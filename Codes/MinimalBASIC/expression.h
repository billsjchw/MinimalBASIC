#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QString>
#include "context.h"

class Expression: public QObject {
public:
    virtual ~Expression();
    virtual int eval(const Context *context) = 0;
    virtual QString toString() = 0;
};

class ConstantExp: public Expression {
public:
    explicit ConstantExp(int constant);
    virtual int eval(const Context *) override;
    virtual QString toString() override;
private:
    int constant;
};

class IdentifierExp: public Expression {
public:
    explicit IdentifierExp(QString identifier);
    virtual int eval(const Context *context) override;
    virtual QString toString() override;
private:
    QString identifier;
};

class CompoundExp: public Expression {
public:
    explicit CompoundExp(const QString &op);
protected:
    QString op;
};

class UnaryCompoundExp: public CompoundExp {
public:
    explicit UnaryCompoundExp(const QString &op, Expression *rhs);
    virtual ~UnaryCompoundExp() override;
    virtual int eval(const Context *context) override;
    virtual QString toString() override;
private:
    Expression *rhs;
};

class BinaryCompoundExp: public CompoundExp {
public:
    explicit BinaryCompoundExp(const QString &op, Expression *lhs, Expression *rhs);
    virtual ~BinaryCompoundExp() override;
    virtual int eval(const Context *context) override;
    virtual QString toString() override;
private:
    Expression *lhs, *rhs;
};

#endif // EXPRESSION_H
