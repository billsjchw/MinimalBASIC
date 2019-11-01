#include <QApplication>
#include "basic_window.h"

int main(int argc, char *argv[]) {
    QApplication minimalBasic(argc, argv);

    BasicWindow basicWindow;
    basicWindow.show();

    return minimalBasic.exec();
}
