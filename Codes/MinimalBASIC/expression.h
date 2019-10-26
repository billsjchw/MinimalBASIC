#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QObject>
#include <QString>
#include "context.h"

class Expression: public QObject {
public:
    explicit Expression(QObject *parent = nullptr);
    virtual int eval(const Context *context) = 0;
    virtual ~Expression();
};

class ConstantExp: public Expression {
private:
    int constant;
public:
    explicit ConstantExp(int constant, QObject *parent = nullptr);
    virtual int eval(const Context *);
};

class IdentifierExp: public Expression {
private:
    QString identifier;
public:
    explicit IdentifierExp(QString identifier, QObject *parent = nullptr);
    virtual int eval(const Context *context);
};

class CompoundExp: public Expression {
private:
    QString op;
    Expression *lhs, *rhs;
public:
    explicit CompoundExp(QString op, Expression *lhs, Expression *rhs, QObject *parent = nullptr);
    virtual int eval(const Context *context);
};

#endif // EXPRESSION_H
