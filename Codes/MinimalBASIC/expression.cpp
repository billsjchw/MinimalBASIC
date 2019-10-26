#include "expression.h"
#include <exception>
#include <QDebug>

Expression::Expression(QObject *parent): QObject(parent) {}

Expression::~Expression() {}

ConstantExp::ConstantExp(int constant, QObject *parent):
    Expression(parent), constant(constant) {}

int ConstantExp::eval(const Context *) {
    return constant;
}

IdentifierExp::IdentifierExp(QString identifier, QObject *parent):
    Expression(parent), identifier(identifier) {}

int IdentifierExp::eval(const Context *context) {
    if (context->isDefined(identifier))
        return context->get(identifier);
    else
        throw std::runtime_error("Identifier " + identifier.toStdString() + " is undefined.");
}

CompoundExp::CompoundExp(QString op, Expression *lhs, Expression *rhs, QObject *parent):
    Expression(parent), op(op), lhs(lhs), rhs(rhs) {
    lhs->setParent(this);
    rhs->setParent(this);
}

int CompoundExp::eval(const Context *context) {
    int lhsValue = lhs->eval(context);
    int rhsValue = rhs->eval(context);
    if (op == "+")
        return lhsValue + rhsValue;
    else if (op == "-")
        return lhsValue - rhsValue;
    else if (op == "*")
        return lhsValue * rhsValue;
    else if (op == "**")
        return lhsValue * rhsValue;
    else if (rhsValue)
        return lhsValue / rhsValue;
    else
        throw std::runtime_error("Division by 0 occurs.");
}
