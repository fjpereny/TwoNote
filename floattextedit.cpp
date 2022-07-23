#include "floattextedit.h"
#include "tabmainwidget.h"
#include "mainwindow.h"

#include <QKeyEvent>
#include <QFocusEvent>
#include <QApplication>
#include <iostream>

FloatTextEdit::FloatTextEdit(QWidget *parent)
{
    this->setParent(parent);
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    this->setStyleSheet
            (   "color: black;"
                "border-width : 4px;"
                "border-style : solid;"
                "border-radius : 4px;"
                "border-color : gray;"
                "background-color : transparent;"
            );

    this->setFontPointSize(12);
    this->setFontFamily("DejaVu Sans");

    selected = new bool(false);
}


FloatTextEdit::~FloatTextEdit()
{

}


void FloatTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete && *selected)
    {
        this->close();
    }

    else
    {
        QTextEdit::keyPressEvent(event);
    }
}


void FloatTextEdit::focusInEvent(QFocusEvent *event)
{
    QWidget *winWidget = QWidget::window();
    MainWindow *win = qobject_cast<MainWindow*>(winWidget);
    win->setCurrentObject(this);

    this->setStyleSheet
            (   "color: black;"
                "border-width : 4px;"
                "border-style : solid;"
                "border-radius : 4px;"
                "border-color : gray;"
                "background-color : transparent;"
            );
}


void FloatTextEdit::focusOutEvent(QFocusEvent *event)
{
    if (this->toPlainText() == "" || this->toPlainText() == "Blank Note")
        this->close();

    *selected = false;

    this->setStyleSheet
            (   "color: black;"
                "border-width : 0px;"
                "background-color : transparent;"
            );

    QTextCursor cursor= this->textCursor();
    cursor.clearSelection();
    this->setTextCursor(cursor);
}


void FloatTextEdit::enterEvent(QEvent *event)
{
    this->setCursor(Qt::IBeamCursor);
}


void FloatTextEdit::leaveEvent(QEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
}


void FloatTextEdit::fontSizeUp()
{

}

void FloatTextEdit::fontSizeDown()
{

}
