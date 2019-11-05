#include "util.h"

const QStringList ops = { "+", "-", "*", "/", "**" };

const QStringList keywords = {
    "rem", "let", "print", "input", "goto", "if", "then", "end",
    "run", "list", "clear", "help", "quit"
};

const QStringList stmtNames = { "rem", "print", "let", "input", "end", "goto", "if" };

const QStringList immStmtNames = { "print", "let", "input" };

const QStringList ctrlCmds = { "list", "clear", "run" };

int intPow(int lhs, int rhs) {
    if (!rhs)
        return 1;
    int ret = intPow(lhs, rhs / 2);
    ret *= ret;
    if (rhs % 2)
        ret *= lhs;
    return ret;
}

int precedence(const QString &op) {
    if (op == "**")
        return 0;
    else if (op == "*" || op == "/")
        return 1;
    else
        return 2;
}

bool isLeftAssociation(int precedence) {
    return precedence;
}
