#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QStringList>

extern const QStringList ops;
extern const QStringList keywords;
extern const QStringList stmtNames;
extern const QStringList immStmtNames;
extern const QStringList ctrlCmds;
int intPow(int lhs, int rhs);
int precedence(const QString &op);
bool isLeftAssociation(int precedence);

#endif // UTIL_H
