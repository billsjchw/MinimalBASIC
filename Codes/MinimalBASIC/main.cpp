#include <QApplication>
#include "basic_window.h"

int main(int argc, char *argv[]) {
    QApplication minimalBasic(argc, argv);

    BasicWindow basicWindow;
    basicWindow.show();

    return minimalBasic.exec();
}

//#include "tokenizer.h"
//#include <QString>
//#include <QRegExp>
//#include <QDebug>

//int main() {
//    Tokenizer tokenizer;

//    qDebug() << tokenizer.tokenize("a--b");

//    return 0;
//}
