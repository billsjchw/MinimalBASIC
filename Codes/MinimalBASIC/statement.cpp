#include "statement.h"
#include <QString>
#include <QStringList>
#include <QRegExp>
#include "tokenizer.h"
#include "parser.h"
#include "error.h"
#include <QDebug>

Statement::~Statement() {}

RemStmt::RemStmt(const QString &cmd) {
    int idxRem = cmd.indexOf("rem");
    comment = cmd.mid(idxRem + 3).trimmed();
}

int RemStmt::exec(Context *) {
    return NextStep::NEXT_STMT;
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

int LetStmt::exec(Context *context) {
    context->setVar(identifier, exp->eval(context));
    return NextStep::NEXT_STMT;
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

int PrintStmt::exec(Context *context) {
    int value = exp->eval(context);
    context->setOutput(QString::number(value));
    return NextStep::WAIT_FOR_OUTPUT;
}

QString PrintStmt::toString() {
    return "PRINT " + exp->toString();
}
