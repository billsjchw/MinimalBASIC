#ifndef STATEMENT_H
#define STATEMENT_H

#include "context.h"
#include <QString>
#include "expression.h"

class Statement {
public:
    enum NextStep { NEXT_STMT = -2, WAIT_FOR_OUTPUT, WAIT_FOR_INPUT };
public:
    virtual ~Statement();
    virtual int exec(Context *context) = 0;
    virtual QString toString() = 0;
};

class RemStmt: public Statement {
public:
    explicit RemStmt(const QString &cmd);
    virtual int exec(Context *) override;
    virtual QString toString() override;
private:
     QString comment;
};

class LetStmt: public Statement {
public:
    explicit LetStmt(const QString &cmd);
    virtual ~LetStmt() override;
    virtual int exec(Context * context) override;
    virtual QString toString() override;
private:
    QString identifier;
    Expression *exp;
};

class PrintStmt: public Statement {
public:
    explicit PrintStmt(const QString &cmd);
    virtual ~PrintStmt() override;
    virtual int exec(Context * context) override;
    virtual QString toString() override;
private:
    Expression *exp;
};

#endif // STATEMENT_H
