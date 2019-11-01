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
    static bool isLeftAssociation(int precedence);
};

#endif // PARSER_H
