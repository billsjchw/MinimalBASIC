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

class IllegalExpression: public Error {
public:
    explicit IllegalExpression(const QString &str);
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

class NonNumericalInput: public Error {
public:
    explicit NonNumericalInput(const QString &input);
};

class InputNumberOutOfRange: public Error {
public:
    explicit InputNumberOutOfRange(const QString &input);
};

class LineNotFound: public Error {
public:
    explicit LineNotFound(int lineNum);
};

class WrongSyntaxForEndStmt: public Error {
public:
    explicit WrongSyntaxForEndStmt();
};

class NoLineNumberInGotoStmt: public Error {
public:
    explicit NoLineNumberInGotoStmt();
};

class NonNumericInLineNumber: public Error {
public:
    explicit NonNumericInLineNumber(const QString &token);
};

class NoThenInIfStmt: public Error {
public:
    explicit NoThenInIfStmt();
};

class NoCondOpInIfStmt: public Error {
public:
    explicit NoCondOpInIfStmt();
};

class NoLineNumberInIfStmt: public Error {
public:
    explicit NoLineNumberInIfStmt();
};

class CannotOpenHelpFile: public Error {
public:
    explicit CannotOpenHelpFile();
};

#endif // ERROR_H
