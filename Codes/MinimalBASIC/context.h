#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QHash>
#include <QString>

class Context {
public:
    void setVar(const QString &identifier, int value);
    int getVar(const QString &identifier) const;
    void setOutput(QString output);
    QString getOutput();
    bool isDefined(const QString &identifier) const;
private:
    QHash<QString, int> vars;
    QString output;
};

#endif // CONTEXT_H
