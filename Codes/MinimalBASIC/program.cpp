#include "program.h"
#include "statement.h"
#include "error.h"

Program::Program(): state(State::END) {}

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

void Program::init() {
    pc = stmts.cbegin();
    state = State::NONE;
}

void Program::run(Context *context) {
    try {
        while (pc != stmts.cend() && state != INPUT && state != OUTPUT)
            pc.value()->exec(this, context);
    } catch (const Error &err) {
        state = State::END;
        throw err;
    }
    if (pc == stmts.cend() && state != OUTPUT)
        state = State::END;
}

void Program::setInput(const QString &input) {
    this->input = input;
    state = AFTER_INPUT;
}

void Program::finishOutput() {
    state = NONE;
}

Program::State Program::getState() {
    return state;
}

QString Program::getOutput() {
    return output;
}

int Program::getErrLineNum() {
    return pc.key();
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

