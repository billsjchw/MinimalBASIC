#include "expression.h"
#include "error.h"
#include "util.h"
#include <QDebug>

Expression::~Expression() {}

ConstantExp::ConstantExp(int constant): constant(constant) {}

int ConstantExp::eval(const Context *) {
    return constant;
}

QString ConstantExp::toString() {
    return QString::number(constant);
}

IdentifierExp::IdentifierExp(QString identifier): identifier(identifier) {}

int IdentifierExp::eval(const Context *context) {
    if (context->isDefined(identifier))
        return context->getVar(identifier);
    else
        throw IdentifierUndefined(identifier);
}

QString IdentifierExp::toString() {
    return identifier;
}

CompoundExp::CompoundExp(const QString &op): op(op) {}

UnaryCompoundExp::UnaryCompoundExp(const QString &op, Expression *rhs):
    CompoundExp(op), rhs(rhs) {}

UnaryCompoundExp::~UnaryCompoundExp() {
    delete rhs;
}

int UnaryCompoundExp::eval(const Context *context) {
    int rhsValue = rhs->eval(context);
    if (op == "u+")
        return rhsValue;
    else
        return -rhsValue;
}

QString UnaryCompoundExp::toString() {
    if (typeid(*rhs) == typeid(BinaryCompoundExp))
        return op.mid(1) + "(" + rhs->toString() + ")";
    else
        return op.mid(1) + rhs->toString();
}

BinaryCompoundExp::BinaryCompoundExp(const QString &op, Expression *lhs, Expression *rhs):
    CompoundExp(op), lhs(lhs), rhs(rhs) {}

BinaryCompoundExp::~BinaryCompoundExp() {
    delete lhs;
    delete rhs;
}

int BinaryCompoundExp::eval(const Context *context) {
    int lhsValue = lhs->eval(context);
    int rhsValue = rhs->eval(context);
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

QString BinaryCompoundExp::toString() {
    QString lhsStr = lhs->toString();
    QString rhsStr = rhs->toString();
    if (typeid(*lhs) == typeid(BinaryCompoundExp)) {
        QString lhsOp = dynamic_cast<BinaryCompoundExp *>(lhs)->op;
        int pl = precedence(lhsOp);
        int pm = precedence(op);
        if (pl > pm || (pl == pm && !isLeftAssociation(pl)))
            lhsStr = "(" + lhsStr + ")";
    }
    if (typeid(*rhs) == typeid(BinaryCompoundExp)) {
        QString rhsOp = dynamic_cast<BinaryCompoundExp *>(rhs)->op;
        int pr = precedence(rhsOp);
        int pm = precedence(op);
        if (pr > pm || (pr == pm && isLeftAssociation(pr)))
            rhsStr = "(" + rhsStr + ")";
    }
    return lhsStr + " " + op + " " + rhsStr;
}
