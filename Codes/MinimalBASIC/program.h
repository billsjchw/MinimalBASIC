#ifndef PROGRAM_H
#define PROGRAM_H

#include <QMap>
#include <QString>
#include "statement.h"

class Program {
public:
    ~Program();
    void setStmt(int lineNum, Statement *stmt);
    void clear();
    QString toString();
private:
    QMap<int, Statement *> stmts;
};

#endif // PROGRAM_H
