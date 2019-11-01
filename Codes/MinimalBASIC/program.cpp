#include "program.h"

Program::~Program() {
    clear();
}

void Program::setStmt(int lineNum, Statement *stmt) {
    if (stmts.contains(lineNum))
        delete stmts.value(lineNum);
    stmts.insert(lineNum, stmt);
}

void Program::clear() {
    for (Statement *stmt: stmts)
        delete stmt;
    stmts.clear();
}

QString Program::toString() {
    QString ret;
    for (auto itr = stmts.cbegin(); itr != stmts.cend(); ++itr) {
        ret.append(QString::number(itr.key()) + " " + itr.value()->toString());
        if (itr + 1 != stmts.end())
            ret.append("\n");
    }
    return ret;
}
