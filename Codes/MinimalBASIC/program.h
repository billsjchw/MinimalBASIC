#ifndef PROGRAM_H
#define PROGRAM_H

#include "context.h"
#include <QMap>
#include <QString>

class Statement;

class Program {
public:
    enum State { NONE, INPUT, OUTPUT, AFTER_INPUT, END };
public:
    explicit Program();
    ~Program();
    void setStmt(int lineNum, Statement *stmt);
    void clear();
    void init();
    void run(Context *context);
    void setInput(const QString &input);
    void finishOutput();
    State getState();
    QString getOutput();
    int getErrLineNum();
    QString toString();
private:
    QMap<int, Statement *> stmts;
    QMap<int, Statement *>::const_iterator pc;
    State state;
    QString input;
    QString output;
friend class RemStmt;
friend class LetStmt;
friend class PrintStmt;
friend class InputStmt;
friend class EndStmt;
friend class GotoStmt;
friend class IfStmt;
};

#endif // PROGRAM_H
