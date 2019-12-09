#ifndef PARSER_H
#define PARSER_H

#include "expression.h"
#include <QString>

class Parser {
public:
    static Expression * parse(const QString &str);
};

#endif // PARSER_H
