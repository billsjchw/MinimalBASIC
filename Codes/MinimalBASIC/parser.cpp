#include "parser.h"
#include <QStack>
#include <QRegExp>
#include "error.h"
#include "util.h"
#include <QDebug>

Expression * Parser::parse(const QStringList &tokens) {
    QStack<QString> opStack;
    QStack<Expression *> expStack;
    try {
        for (int i = 0; i < tokens.size(); ++i) {
            QString token = tokens.at(i);
            if (ops.contains(token)) {
                while (!opStack.empty() && ops.contains(opStack.top())) {
                    int pl = precedence(opStack.top());
                    int pr = precedence(token);
                    if (pl < pr || (pl == pr && isLeftAssociation(pl))) {
                        Expression *rhs = expStack.pop();
                        Expression *lhs = expStack.pop();
                        expStack.push(new CompoundExp(opStack.top(), lhs, rhs));
                        opStack.pop();
                    } else
                        break;
                }
                opStack.push(token);
            } else if (token == "(")
                opStack.push("(");
            else if (token == ")") {
                while (!opStack.empty() && opStack.top() != "(") {
                    Expression *rhs = expStack.pop();
                    Expression *lhs = expStack.pop();
                    expStack.push(new CompoundExp(opStack.top(), lhs, rhs));
                    opStack.pop();
                }
               opStack.pop();
            } else if (QRegExp("\\d+").exactMatch(token)) {
                bool inRange;
                int constant = token.toInt(&inRange);
                if (!inRange)
                    throw ConstantOutOfRange(token);
                else
                    expStack.push(new ConstantExp(constant));
            } else {
                if (!QRegExp("[a-z_][a-z0-9_]*").exactMatch(token) || keywords.contains(token))
                    throw InvalidIndentifier(token);
                else
                    expStack.push(new IdentifierExp(token));
            }
        }
        while (!opStack.empty()) {
            Expression *rhs = expStack.pop();
            Expression *lhs = expStack.pop();
            expStack.push(new CompoundExp(opStack.top(), lhs, rhs));
            opStack.pop();
        }
    } catch (const Error &err) {
        while (!expStack.empty()) {
            delete expStack.pop();
            throw err;
        }
    }
    return expStack.top();
}
