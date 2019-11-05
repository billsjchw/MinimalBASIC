#include "statement.h"
#include <QString>
#include <QStringList>
#include <QRegExp>
#include "tokenizer.h"
#include "parser.h"
#include "error.h"
#include "program.h"
#include "util.h"
#include <QDebug>

Statement::~Statement() {}

RemStmt::RemStmt(const QString &cmd) {
    int idxRem = cmd.indexOf("rem");
    comment = cmd.mid(idxRem + 3).trimmed();
}

void RemStmt::exec(Program *prog, Context *) {
    ++prog->pc;
}

QString RemStmt::toString() {
    return "REM " + comment;
}

LetStmt::LetStmt(const QString &cmd) {
    int idxLet = cmd.indexOf("let");
    int idxAssignment = cmd.indexOf('=');
    if (idxAssignment == -1)
        throw NoAssignmentInLetStmt();
    QString token = cmd.mid(idxLet + 3, idxAssignment - (idxLet + 3)).trimmed();
    if (!QRegExp("[a-z_][a-z0-9_]*").exactMatch(token) || keywords.contains(token))
        throw InvalidIndentifier(token);
    else
        identifier = token;
    QString str = cmd.mid(idxAssignment + 1);
    exp = Parser::parse(Tokenizer::tokenize(str));
}

LetStmt::~LetStmt() {
    delete exp;
}

void LetStmt::exec(Program *prog, Context *context) {
    context->setVar(identifier, exp->eval(context));
    ++prog->pc;
}

QString LetStmt::toString() {
    return "LET " + identifier + " = " + exp->toString();
}

PrintStmt::PrintStmt(const QString &cmd) {
    int idxPrint = cmd.indexOf("print");
    QString str = cmd.mid(idxPrint + 5);
    exp = Parser::parse(Tokenizer::tokenize(str));
}

PrintStmt::~PrintStmt() {
    delete exp;
}

void PrintStmt::exec(Program *prog, Context *context) {
    int value = exp->eval(context);
    prog->output = QString::number(value);
    prog->state = Program::State::OUTPUT;
    ++prog->pc;
}

QString PrintStmt::toString() {
    return "PRINT " + exp->toString();
}

InputStmt::InputStmt(const QString &cmd) {
    int idxInput = cmd.indexOf("input");
    QString token = cmd.mid(idxInput + 5).trimmed();
    if (!QRegExp("[a-z_][a-z0-9_]*").exactMatch(token) || keywords.contains(token))
        throw InvalidIndentifier(token);
    else
        identifier = token;
}

void InputStmt::exec(Program *prog, Context *context) {
    if (prog->state == Program::State::NONE)
        prog->state = Program::State::INPUT;
    else {
        QString input = prog->input.trimmed();
        if (!QRegExp("[-+]?\\d+").exactMatch(input))
            throw NonNumericalInput(input);
        else {
            bool inRange;
            int value = input.toInt(&inRange);
            if (!inRange)
                throw InputNumberOutOfRange(input);
            else {
                context->setVar(identifier, value);
                ++prog->pc;
                prog->state = Program::State::NONE;
            }
        }
    }
}

QString InputStmt::toString() {
    return "INPUT " + identifier;
}

EndStmt::EndStmt(const QString &cmd) {
    int idxEnd = cmd.indexOf("end");
    if (cmd.mid(idxEnd + 3).length())
        throw WrongSyntaxForEndStmt();
}

void EndStmt::exec(Program *prog, Context *) {
    prog->pc = prog->stmts.cend();
}

QString EndStmt::toString() {
    return "END";
}

GotoStmt::GotoStmt(const QString &cmd) {
    int idxGoto = cmd.indexOf("goto");
    QString token = cmd.mid(idxGoto + 4).trimmed();
    if (!token.length())
        throw NoLineNumberInGotoStmt();
    else if (!QRegExp("\\d+").exactMatch(token))
        throw NonNumericInLineNumber(token);
    else {
        bool inRange;
        lineNum = token.toInt(&inRange);
        if (!inRange || !lineNum)
            throw LineNumberOutOfRange(token);
    }
}

void GotoStmt::exec(Program *prog, Context *) {
    if (!prog->stmts.contains(lineNum))
        throw LineNotFound(lineNum);
    else
        prog->pc = prog->stmts.constFind(lineNum);
}

QString GotoStmt::toString() {
    return "GOTO " + QString::number(lineNum);
}

IfStmt::IfStmt(const QString &cmd) {
    int idxIf = cmd.indexOf("if");
    int idxThen = cmd.indexOf(QRegExp("\\sthen\\s"));
    if (idxThen == -1)
        throw NoThenInIfStmt();
    QString token = cmd.mid(idxThen + 6).trimmed();
    if (!token.length())
        throw NoLineNumberInIfStmt();
    else if (!QRegExp("\\d+").exactMatch(token))
        throw NonNumericInLineNumber(token);
    else {
        bool inRange;
        lineNum = token.toInt(&inRange);
        if (!inRange || !lineNum)
            throw LineNumberOutOfRange(token);
    }
    QString str = cmd.mid(idxIf + 2, idxThen - idxIf - 2);
    int idxCondOp = str.indexOf(QRegExp("[<=>]"));
    if (idxCondOp == -1)
        throw NoCondOpInIfStmt();
    condOp = str.at(idxCondOp);
    QString lhsStr = str.mid(0, idxCondOp);
    QString rhsStr = str.mid(idxCondOp + 1);
    lhs = Parser::parse(Tokenizer::tokenize(lhsStr));
    try {
        rhs = Parser::parse(Tokenizer::tokenize(rhsStr));
    } catch (const Error &) {
        delete lhs;
    }
}

IfStmt::~IfStmt() {
    delete lhs;
    delete rhs;
}

void IfStmt::exec(Program *prog, Context *context) {
    int lhsValue = lhs->eval(context);
    int rhsValue = rhs->eval(context);
    if ((condOp == "<" && lhsValue < rhsValue) || ((condOp == "=" && lhsValue == rhsValue)) || (condOp == ">" && lhsValue > rhsValue)) {
        if (!prog->stmts.contains(lineNum))
            throw LineNotFound(lineNum);
        else
            prog->pc = prog->stmts.constFind(lineNum);
    } else
        ++prog->pc;
}

QString IfStmt::toString() {
    return "IF " + lhs->toString() + " " + condOp + " " + rhs->toString() + " THEN " + QString::number(lineNum);
}
