#include "tokenizer.h"
#include <QRegExp>

QStringList Tokenizer::tokenize(const QString &str) {
    QStringList ret;
    QString special = "+-*/()";
    QString whitespace = " \f\r\v\t\n";
    QString token;
    for (int i = 0; i < str.length(); ++i)
        if (QRegExp("\\s").exactMatch(str.at(i)))
            continue;
        else if (special.contains(str.at(i))) {
            if (token.length()) {
                ret.append(token);
                token.clear();
            }
            if (i + 1 < str.length() && str.mid(i, 2) == "**") {
                ret.append("**");
                ++i;
            } else
                ret.append(str.at(i));
        } else
            token.append(str.at(i));
    if (token.length())
        ret.append(token);
    return ret;
}
