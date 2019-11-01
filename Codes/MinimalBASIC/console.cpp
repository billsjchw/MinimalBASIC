#include "console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>
#include <QString>
#include <QDebug>

Console::Console(QWidget *parent) : QTextEdit(parent) {}

void Console::write(QString msg)
{
    QString content = this->toPlainText();
    content.append(msg + "\n");
    this->setText(content);
    QTextCursor cursor = this->textCursor();
    cursor.movePosition(QTextCursor::End);
    this->setTextCursor(cursor);
}

void Console::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace)
        return;
    if (event->key() == Qt::Key_Delete)
        return;
    if (this->textCursor().hasSelection())
        return;
    if (event->key() == Qt::Key_Return) {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        QString lastLine = cursor.selectedText();
        QTextEdit::keyPressEvent(event);
        newCommandWritten(lastLine);
    } else
        QTextEdit::keyPressEvent(event);
}
