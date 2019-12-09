#ifndef STATEMENT_H
#define STATEMENT_H

#include "context.h"
#include "program.h"
#include "expression.h"
#include <QString>

class Statement {
public:
    virtual ~Statement();
    virtual void exec(Program *prog, Context *context) = 0;
    virtual QString toString() = 0;
};

class RemStmt: public Statement {
public:
    explicit RemStmt(const QString &cmd);
    virtual void exec(Program *prog, Context *) override;
    virtual QString toString() override;
private:
     QString comment;
};

class LetStmt: public Statement {
public:
    explicit LetStmt(const QString &cmd);
    virtual ~LetStmt() override;
    virtual void exec(Program *prog, Context *context) override;
    virtual QString toString() override;
private:
    QString identifier;
    Expression *exp;
};

class PrintStmt: public Statement {
public:
    explicit PrintStmt(const QString &cmd);
    virtual ~PrintStmt() override;
    virtual void exec(Program *prog, Context *context) override;
    virtual QString toString() override;
private:
    Expression *exp;
};

class InputStmt: public Statement {
public:
    explicit InputStmt(const QString &cmd);
    virtual void exec(Program *prog, Context *context) override;
    virtual QString toString() override;
private:
    QString identifier;
};

class EndStmt: public Statement {
public:
    explicit EndStmt(const QString &cmd);
    virtual void exec(Program *prog, Context *) override;
    virtual QString toString() override;
};

class GotoStmt: public Statement {
public:
    explicit GotoStmt(const QString &cmd);
    virtual void exec(Program *prog, Context *) override;
    virtual QString toString() override;
private:
    int lineNum;
};

class IfStmt: public Statement {
public:
    explicit IfStmt(const QString &cmd);
    virtual ~IfStmt() override;
    virtual void exec(Program *prog, Context *context) override;
    virtual QString toString() override;
private:
    Expression *lhs, *rhs;
    QString condOp;
    int lineNum;
};

#endif // STATEMENT_H
