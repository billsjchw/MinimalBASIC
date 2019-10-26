#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include <QHash>
#include <QString>

class Context: public QObject {
private:
    QHash<QString, int> vars;
public:
    explicit Context(QObject *parent = nullptr);
    void set(const QString &identifier, int value);
    int get(const QString &identifier) const;
    bool isDefined(const QString &identifier) const;
};

#endif // CONTEXT_H
