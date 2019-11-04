#ifndef ERROR_H
#define ERROR_H

#include <QString>
#include <exception>

class Error {
public:
    explicit Error();
    explicit Error(const QString &explanation);
    QString what() const;
private:
    QString explanation;
};

class IdentifierUndefined: public Error {
public:
    explicit IdentifierUndefined(const QString &identifier);
};

class NegtivePowRhs: public Error {
public:
    explicit NegtivePowRhs();
};

class ZeroPowZero: public Error {
public:
    explicit ZeroPowZero();
};

class DivisionByZero: public Error {
public:
    explicit DivisionByZero();
};

class ConstantOutOfRange: public Error {
public:
    explicit ConstantOutOfRange(const QString &token);
};

class InvalidIndentifier: public Error {
public:
    explicit InvalidIndentifier(const QString &token);
};

class LineNumberOutOfRange: public Error {
public:
    explicit LineNumberOutOfRange(const QString &token);
};

class NoAssignmentInLetStmt: public Error {
public:
    explicit NoAssignmentInLetStmt();
};

class MissingStmtName: public Error {
public:
    explicit MissingStmtName();
};

class WrongStmtName: public Error {
public:
    explicit WrongStmtName(const QString &name);
};

class StmtCannotImmExec: public Error {
public:
    explicit StmtCannotImmExec(const QString &name);
};

class LineNotFound: public Error {
public:
    explicit LineNotFound(int lineNum);
};

#endif // ERROR_H
