#include "error.h"
#include <climits>

Error::Error():
    explanation("An Unknown error occurred.") {}

Error::Error(const QString &explanation): explanation(explanation) {}

QString Error::what() const {
    return explanation;
}

IdentifierUndefined::IdentifierUndefined(const QString &identifier):
    Error("Identifier \"" + identifier + "\" is undefined.") {}

NegtivePowRhs::NegtivePowRhs():
    Error("The right-hand side operand of ** should be nonnegative.") {}

ZeroPowZero::ZeroPowZero():
    Error("0 ** 0 occurred.") {}

DivisionByZero::DivisionByZero():
    Error("Division by 0 occurred.") {}

ConstantOutOfRange::ConstantOutOfRange(const QString &token):
    Error("Constant " + token + " is out of the range [0, " + QString::number(INT_MAX) + "].") {}

InvalidIndentifier::InvalidIndentifier(const QString &token):
    Error("\"" + token + "\" is not a valid identifier.") {}

LineNumberOutOfRange::LineNumberOutOfRange(const QString &token):
    Error("Line number " + token + " is out of the range [1, " + QString::number(INT_MAX) + "].") {}

NoAssignmentInLetStmt::NoAssignmentInLetStmt():
    Error("No \"=\" token is found in LET statement.") {}

MissingStmtName::MissingStmtName():
    Error("Statement name is missing.") {}

WrongStmtName::WrongStmtName(const QString &name):
    Error("No statement is named \"" + name.toUpper() + "\".") {}

StmtCannotImmExec::StmtCannotImmExec(const QString &name):
    Error(name.toUpper() + " statement cannot be executed immediately.") {}

NonNumericalInput::NonNumericalInput(const QString &input):
    Error("Input \"" + input + "\" is non-numerical.") {}

InputNumberOutOfRange::InputNumberOutOfRange(const QString &input):
    Error("Input number " + input + " is out of the range [" + QString::number(INT_MIN) + ", " + QString::number(INT_MAX) + "].") {}

LineNotFound::LineNotFound(int lineNum):
    Error("Line " + QString::number(lineNum) + " doesn't exist.") {}

WrongSyntaxForEndStmt::WrongSyntaxForEndStmt():
    Error("The END statement is not in correct syntax.") {}

NoLineNumberInGotoStmt::NoLineNumberInGotoStmt():
    Error("No line number is found in GOTO statement.") {}

NonNumericInLineNumber::NonNumericInLineNumber(const QString &token):
    Error("\"" + token + "\" contains non-numeric character(s).") {}

NoThenInIfStmt::NoThenInIfStmt():
    Error("No \"THEN\" token is found in IF statement.") {}

NoCondOpInIfStmt::NoCondOpInIfStmt():
    Error("No conditional operator is found in IF statement.") {}

NoLineNumberInIfStmt::NoLineNumberInIfStmt():
    Error("No line number is found in IF statement.") {}
