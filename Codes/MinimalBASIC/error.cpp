#include "error.h"
#include <climits>

Error::~Error() {}

QString Error::what() const {
    return "Something wrong occurred";
}

IdentifierUndefined::IdentifierUndefined(const QString &identifier): identifier(identifier) {}

QString IdentifierUndefined::what() const {
    return "Identifier \"" + identifier + "\" is undefined.";
}

QString NegtivePowRhs::what() const {
    return "The right-hand side operand of ** should be nonnegative.";
}

QString ZeroPowZero::what() const {
    return "0 ** 0 occurred.";
}

QString DivisionByZero::what() const {
    return "Division by 0 occurred.";
}

ConstantOutOfRange::ConstantOutOfRange(const QString &token): token(token) {}

QString ConstantOutOfRange::what() const {
    return "Constant \"" + token + "\" is out of range ([0, " + QString::number(INT_MAX) + "])";
}

InvalidIdentifier::InvalidIdentifier(const QString &token): token(token) {}

QString InvalidIdentifier::what() const {
    return "\"" + token + "\" is not a valid identifier.";
}

WrongExpression::WrongExpression(const QString &str): str(str) {}

QString WrongExpression::what() const {
    return "\"" + str + "\" is not an expression.";
}
