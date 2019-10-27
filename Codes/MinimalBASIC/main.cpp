#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "context.h"
#include "expression.h"
#include "tokenizer.h"
#include "parser.h"
#include "error.h"
#include <QString>

int main(int argc, char *argv[]) {
    QCoreApplication minimalBasic(argc, argv);

    Context *context = new Context();
    context->set("x", 10);

    Expression *exp = nullptr;
    try {
        exp = Parser::parse(Tokenizer::tokenize("1 - 2 ** x * 3 - (x + 7)"));
        qDebug() << exp->eval(context);
    } catch (const Error &err) {
        qDebug() << err.what();
    }

    delete exp;
    delete context;

    QTimer::singleShot(0, &minimalBasic, QCoreApplication::quit);
    return minimalBasic.exec();
}
