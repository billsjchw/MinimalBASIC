#include "basic_window.h"
#include <QString>
#include <QStringList>
#include <QRegExp>
#include "statement.h"
#include "error.h"
#include "util.h"
#include <QDebug>

BasicWindow::BasicWindow(QWidget *parent): QWidget(parent) {
    setWindowTitle("BASIC");
    setFixedSize(800, 900);
    console = new Console(this);
    console->setGeometry(30, 30, 740, 840);
    connect(console, &Console::newCommandWritten, this, &BasicWindow::handleNewCommand);
    context = new Context();
    prog = new Program();
    immProg = new Program();
}

BasicWindow::~BasicWindow() {
    delete context;
    delete prog;
    delete immProg;
}

void BasicWindow::handleNewCommand(QString cmd) {
    try {
        cmd = cmd.toLower().trimmed();
        if (ctrlCmds.contains(cmd)) {
            if (cmd == "list")
                console->write(prog->toString());
            else if (cmd == "clear")
                prog->clear();
            else {
                prog->init();
                runProgAndOutput(prog);
            }
        } else {
            QStringList parts = cmd.split(QRegExp("\\s+"), QString::SplitBehavior::SkipEmptyParts);
            if (parts.empty())
                return;
            int lineNum = -1;
            if (QRegExp("\\d+").exactMatch(parts.first())) {
                bool inRange;
                lineNum = parts.first().toInt(&inRange);
                if (!inRange || !lineNum)
                    throw LineNumberOutOfRange(parts.first());
                parts.removeFirst();
            }
            if (parts.empty())
                throw MissingStmtName();
            QString name = parts.first();
            if (!stmtNames.contains(name))
                throw WrongStmtName(name);
            if (lineNum == -1 && !immStmtNames.contains(name))
                throw StmtCannotImmExec(name);
            Statement *stmt;
            if (name == "rem")
                stmt = new RemStmt(cmd);
            else if (name == "print")
                stmt = new PrintStmt(cmd);
            else
                stmt = new LetStmt(cmd);
            if (lineNum == -1) {
                immProg->setStmt(1, stmt);
                immProg->init();
                runProgAndOutput(immProg);
            }
            else
                prog->setStmt(lineNum, stmt);
        }
    } catch (const Error &err) {
        console->write(err.what());
    }
}

void BasicWindow::runProgAndOutput(Program *prog) {
    while (prog->getState() != Program::State::INPUT && prog->getState() != Program::State::END) {
        try {
            prog->run(context);
        } catch (const Error &err) {
            console->write("[Line " + QString::number(prog->getErrLineNum()) + "] " + err.what());
        }
        if (prog->getState() == Program::State::OUTPUT) {
            console->write(prog->getOutput());
            prog->finishOutput();
        }
    }
}
