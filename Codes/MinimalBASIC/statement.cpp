#include "statement.h"
#include <QString>
#include <QStringList>
#include <QRegExp>
#include "tokenizer.h"
#include "parser.h"
#include "error.h"
#include "program.h"
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
    QStringList keywords = {
        "rem", "let", "print", "input", "goto", "if", "then", "end",
        "run", "list", "clear", "help", "quit"
    };
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
