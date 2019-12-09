#include "tokenizer.h"
#include "util.h"
#include <QRegExp>

QStringList Tokenizer::tokenize(const QString &str) {
    QStringList ret;
    QStringList parts = str.split(QRegExp("\\s"), QString::SplitBehavior::SkipEmptyParts);
    for (const QString &part: parts) {
        QString special = "+-*/()";
        QString token;
        for (int i = 0; i < part.length(); ++i)
            if (special.contains(part.at(i))) {
                if (token.length()) {
                    ret.append(token);
                    token.clear();
                }
                if (i + 1 < part.length() && part.mid(i, 2) == "**") {
                    ret.append("**");
                    ++i;
                } else
                    ret.append(part.at(i));
            } else
                token.append(part.at(i));
        if (token.length())
            ret.append(token);
    }
    for (int i = 0; i < ret.length(); ++i)
        if ((ret.at(i) == "+" || ret.at(i) == "-") && (!i || ret.at(i - 1) == "(" || ops.contains(ret.at(i - 1))))
            ret.replace(i, "u" + ret.at(i));
    return ret;
}
