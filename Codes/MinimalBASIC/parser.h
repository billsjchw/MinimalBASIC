#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QStringList>
#include "expression.h"

class Parser {
public:
    static Expression * parse(const QStringList &tokens);
private:
    static int precedence(const QString &op);
    static bool isLeftPrecedence(int precedence);
    static bool isNumericString(const QString &str);
    static bool isValidIdentifier(const QString &identifier);
};

#endif // PARSER_H
