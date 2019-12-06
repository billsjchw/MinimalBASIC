#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include "expression.h"

class Parser {
public:
    static Expression * parse(const QString &str);
};

#endif // PARSER_H
