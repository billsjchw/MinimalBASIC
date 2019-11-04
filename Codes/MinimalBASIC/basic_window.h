#ifndef BASIC_WINDOW_H
#define BASIC_WINDOW_H

#include <QWidget>
#include "console.h"
#include <QString>
#include "context.h"
#include "program.h"

class BasicWindow: public QWidget {
    Q_OBJECT
public:
    explicit BasicWindow(QWidget *parent = nullptr);
    ~BasicWindow();
private slots:
    void handleNewCommand(QString cmd);
private:
    Console *console;
    Context *context;
    Program *prog;
    Program *immProg;
    void runProgAndOutput(Program *prog);
};

#endif // BASIC_WINDOW_H
