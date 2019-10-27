#include "parser.h"
#include <QStack>
#include <QRegExp>
#include "error.h"
#include <QDebug>

Expression * Parser::parse(const QStringList &tokens) {
    QStack<QString> opStack;
    QStack<Expression *> expStack;
    QStringList opList = {"+", "-", "*", "/", "**"};
    try {
        for (int i = 0; i < tokens.size(); ++i) {
            QString token = tokens.at(i);
            if (opList.contains(token)) {
                while (!opStack.empty() && opList.contains(opStack.top())) {
                    int pl = precedence(opStack.top());
                    int pr = precedence(token);
                    if (pl < pr || (pl == pr && isLeftPrecedence(pl))) {
                        if (expStack.size() < 2)
                            throw WrongExpression(tokens.join(""));
                        else {
                            Expression *rhs = expStack.pop();
                            Expression *lhs = expStack.pop();
                            expStack.push(new CompoundExp(opStack.top(), lhs, rhs));
                            opStack.pop();
                        }
                    } else
                        break;
                }
                opStack.push(token);
            } else if (token == "(") {
                if (i + 1 < tokens.size() && tokens.at(i + 1) == ")")
                    throw WrongExpression(tokens.join(""));
                else
                    opStack.push("(");
            } else if (token == ")") {
                while (!opStack.empty() && opStack.top() != "(") {
                    if (expStack.size() < 2)
                        throw WrongExpression(tokens.join(""));
                    else {
                        Expression *rhs = expStack.pop();
                        Expression *lhs = expStack.pop();
                        expStack.push(new CompoundExp(opStack.top(), lhs, rhs));
                    }
                    opStack.pop();
                }
                if (opStack.empty())
                    throw WrongExpression(tokens.join(""));
                else
                    opStack.pop();
            } else if (isNumericString(token)) {
                bool inRange;
                int constant = token.toInt(&inRange);
                if (!inRange)
                    throw ConstantOutOfRange(token);
                else
                    expStack.push(new ConstantExp(constant));
            } else {
                if (!isValidIdentifier(token))
                    throw InvalidIdentifier(token);
                else
                    expStack.push(new IdentifierExp(token));
            }
        }
        while (!opStack.empty() && opList.contains(opStack.top())) {
            if (expStack.size() < 2)
                throw WrongExpression(tokens.join(""));
            else {
                Expression *rhs = expStack.pop();
                Expression *lhs = expStack.pop();
                expStack.push(new CompoundExp(opStack.top(), lhs, rhs));
            }
            opStack.pop();
        }
        if (!opStack.empty() || expStack.size() != 1)
            throw WrongExpression(tokens.join(""));
    } catch (const Error &err) {
        while (!expStack.empty()) {
            delete expStack.top();
            expStack.pop();
        }
        throw err;
    }
    return expStack.top();
}

int Parser::precedence(const QString &op) {
    if (op == "**")
        return 0;
    else if (op == "*" || op == "/")
        return 1;
    else
        return 2;
}

bool Parser::isLeftPrecedence(int precedence) {
    return precedence;
}

bool Parser::isNumericString(const QString &str) {
    QRegExp regExp("\\d*");
    return regExp.exactMatch(str);
}

bool Parser::isValidIdentifier(const QString &identifier) {
    return true;
}
