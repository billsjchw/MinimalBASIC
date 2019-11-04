#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QHash>
#include <QString>

class Context {
public:
    void setVar(const QString &identifier, int value);
    int getVar(const QString &identifier) const;
    bool isDefined(const QString &identifier) const;
private:
    QHash<QString, int> vars;
};

#endif // CONTEXT_H
