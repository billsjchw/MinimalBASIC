#ifndef ERROR_H
#define ERROR_H

#include <QString>
#include <exception>

class Error {
public:
    virtual QString what() const;
    virtual ~Error();
};

class IdentifierUndefined: public Error {
public:
    explicit IdentifierUndefined(const QString &identifier);
    virtual QString what() const override;
private:
    QString identifier;
};

class NegtivePowRhs: public Error {
public:
    virtual QString what() const override;
};

class ZeroPowZero: public Error {
public:
    virtual QString what() const override;
};

class DivisionByZero: public Error {
public:
    virtual QString what() const override;
};

class ConstantOutOfRange: public Error {
public:
    explicit ConstantOutOfRange(const QString &token);
    virtual QString what() const override;
private:
    QString token;
};

class InvalidIdentifier: public Error {
public:
    explicit InvalidIdentifier(const QString &token);
    virtual QString what() const override;
private:
    QString token;
};

class WrongExpression: public Error {
public:
    explicit WrongExpression(const QString &str);
    virtual QString what() const override;
private:
    QString str;
};

#endif // ERROR_H
