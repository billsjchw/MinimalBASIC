#include "basic_window.h"
#include <QString>
#include <QStringList>
#include <QRegExp>
#include "statement.h"
#include "error.h"
#include <QDebug>

BasicWindow::BasicWindow(QWidget *parent): QWidget(parent) {
    setWindowTitle("BASIC");
    setFixedSize(800, 900);
    console = new Console(this);
    console->setGeometry(30, 30, 740, 840);
    connect(console, &Console::newCommandWritten, this, &BasicWindow::handleNewCommand);
    context = new Context();
    program = new Program();
}

BasicWindow::~BasicWindow() {
    delete context;
    delete program;
}

void BasicWindow::handleNewCommand(QString cmd) {
    QStringList stmtName = { "rem", "print", "let" };
    QStringList immStmtName = { "print", "let" };
    QStringList ctrlCmd = { "list", "clear" };
    try {
        cmd = cmd.toLower().trimmed();
        if (ctrlCmd.contains(cmd)) {
            if (cmd == "list")
                console->write(program->toString());
            else
                program->clear();
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
            if (!stmtName.contains(name))
                throw WrongStmtName(name);
            if (lineNum == -1 && !immStmtName.contains(name))
                throw StmtCannotImmExec(name);
            Statement *stmt;
            if (name == "rem")
                stmt = new RemStmt(cmd);
            else if (name == "print")
                stmt = new PrintStmt(cmd);
            else
                stmt = new LetStmt(cmd);
            if (lineNum == -1)
                try {
                    int nextStep = stmt->exec(context);
                    if (nextStep == Statement::NextStep::WAIT_FOR_OUTPUT)
                        console->write(context->getOutput());
                } catch (const Error &err) {
                    delete stmt;
                    throw err;
                }
            else
                program->setStmt(lineNum, stmt);
        }
    } catch (const Error &err) {
        console->write(err.what());
    }
}
