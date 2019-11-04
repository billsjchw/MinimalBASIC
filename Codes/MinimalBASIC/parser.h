#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QStringList>
#include "expression.h"

class Parser {
public:
    static Expression * parse(const QStringList &tokens);
};

#endif // PARSER_H
