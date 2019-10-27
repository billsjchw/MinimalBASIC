#include "expression.h"
#include "error.h"
#include <QDebug>

Expression::~Expression() {}

ConstantExp::ConstantExp(int constant): constant(constant) {}

int ConstantExp::eval(const Context *) {
    return constant;
}

IdentifierExp::IdentifierExp(QString identifier): identifier(identifier) {}

int IdentifierExp::eval(const Context *context) {
    if (context->isDefined(identifier))
        return context->get(identifier);
    else
        throw IdentifierUndefined(identifier);
}

CompoundExp::CompoundExp(QString op, Expression *lhs, Expression *rhs):
    op(op), lhs(lhs), rhs(rhs) {}

CompoundExp::~CompoundExp() {
    delete lhs;
    delete rhs;
}

int CompoundExp::eval(const Context *context) {
    int lhsValue = lhs->eval(context);
    int rhsValue = rhs->eval(context);
//    qDebug() << lhsValue << op << rhsValue;
    if (op == "+")
        return lhsValue + rhsValue;
    else if (op == "-")
        return lhsValue - rhsValue;
    else if (op == "*")
        return lhsValue * rhsValue;
    else if (op == "**") {
        if (rhsValue < 0)
            throw NegtivePowRhs();
        else if (!lhsValue && !rhsValue)
            throw ZeroPowZero();
        else
            return intPow(lhsValue, rhsValue);
    } else {
        if (rhsValue)
            return lhsValue / rhsValue;
        else
            throw DivisionByZero();
    }
}

int CompoundExp::intPow(int lhs, int rhs) {
    if (!rhs)
        return 1;
    int ret = intPow(lhs, rhs / 2);
    ret *= ret;
    if (rhs % 2)
        ret *= lhs;
    return ret;
}
