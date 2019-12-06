#include "parser.h"
#include "tokenizer.h"
#include "error.h"
#include "util.h"
#include <QStringList>
#include <QStack>
#include <QRegExp>
#include <QDebug>

Expression * Parser::parse(const QString &str) {
    QStringList tokens = Tokenizer::tokenize(str);
    for (int i = 0; i + 1 < tokens.size(); ++i)
        if ((tokens.at(i) == "(" && tokens.at(i + 1) == ")") ||
                (tokens.at(i) == ")" && tokens.at(i + 1) == "(") ||
                (tokens.at(i) != "(" && tokens.at(i) != ")" &&
                 tokens.at(i + 1) != "(" && tokens.at(i + 1) != ")" &&
                 !ops.contains(tokens.at(i)) && !ops.contains(tokens.at(i + 1))))
            throw IllegalExpression(str.trimmed());
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
                        if (opStack.top().front() == 'u') {
                            if (expStack.empty())
                                throw IllegalExpression(str.trimmed());
                            Expression *rhs = expStack.pop();
                            expStack.push(new UnaryCompoundExp(opStack.top(), rhs));
                            opStack.pop();
                        } else {
                            if (expStack.size() < 2)
                                throw IllegalExpression(str.trimmed());
                            Expression *rhs = expStack.pop();
                            Expression *lhs = expStack.pop();
                            expStack.push(new BinaryCompoundExp(opStack.top(), lhs, rhs));
                            opStack.pop();
                        }
                    } else
                        break;
                }
                opStack.push(token);
            } else if (token == "(")
                opStack.push("(");
            else if (token == ")") {
                while (!opStack.empty() && opStack.top() != "(")
                    if (opStack.top().front() == 'u') {
                        if (expStack.empty())
                            throw IllegalExpression(str.trimmed());
                        Expression *rhs = expStack.pop();
                        expStack.push(new UnaryCompoundExp(opStack.top(), rhs));
                        opStack.pop();
                    } else {
                        if (expStack.size() < 2)
                            throw IllegalExpression(str.trimmed());
                        Expression *rhs = expStack.pop();
                        Expression *lhs = expStack.pop();
                        expStack.push(new BinaryCompoundExp(opStack.top(), lhs, rhs));
                        opStack.pop();
                    }
                if (opStack.empty())
                    throw IllegalExpression(str.trimmed());
                opStack.pop();
            } else if (QRegExp("\\d+").exactMatch(token)) {
                bool inRange;
                int constant = token.toInt(&inRange);
                if (!inRange)
                    throw ConstantOutOfRange(token);
                else
                    expStack.push(new ConstantExp(constant));
            } else {
                if (!QRegExp("[a-z_][a-z\\d_]*").exactMatch(token) || keywords.contains(token))
                    throw InvalidIndentifier(token);
                else
                    expStack.push(new IdentifierExp(token));
            }
        }
        while (!opStack.empty())
            if (!ops.contains(opStack.top()))
                throw IllegalExpression(str.trimmed());
            else if (opStack.top().front() == 'u') {
                if (expStack.empty())
                    throw IllegalExpression(str.trimmed());
                Expression *rhs = expStack.pop();
                expStack.push(new UnaryCompoundExp(opStack.top(), rhs));
                opStack.pop();
            } else {
                if (expStack.size() < 2)
                    throw IllegalExpression(str.trimmed());
                Expression *rhs = expStack.pop();
                Expression *lhs = expStack.pop();
                expStack.push(new BinaryCompoundExp(opStack.top(), lhs, rhs));
                opStack.pop();
            }
        if (expStack.size() != 1)
            throw IllegalExpression(str.trimmed());
    } catch (const Error &err) {
        while (!expStack.empty())
            delete expStack.pop();
        throw err;
    }
    return expStack.top();
}
