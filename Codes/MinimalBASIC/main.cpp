#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "context.h"
#include "expression.h"
#include "tokenizer.h"
#include <exception>

int main(int argc, char *argv[]) {
    QCoreApplication minimalBasic(argc, argv);

    Context *context = new Context();
    context->set("x", 10);

    ConstantExp *constantExp = new ConstantExp(20);
    IdentifierExp *identifierExp = new IdentifierExp("x");
    CompoundExp *compoundExp = new CompoundExp("/", constantExp, identifierExp);

    try {
        int value = compoundExp->eval(context);
        qDebug() << value;
    } catch (const std::exception &e) {
        qDebug() << e.what();
    }

    context->deleteLater();
    compoundExp->deleteLater();

    QTimer::singleShot(0, &minimalBasic, QCoreApplication::quit);
    return minimalBasic.exec();
}
