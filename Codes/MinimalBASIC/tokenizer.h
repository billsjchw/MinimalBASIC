#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <QObject>
#include <QString>
#include <QStringList>

class Tokenizer: public QObject {
public:
    explicit Tokenizer(QObject *parent = nullptr);
    static QStringList tokenize(const QString &str);
};

#endif // TOKENIZER_H
