#include "floattextedit.h"
#include "tabmainwidget.h"
#include "mainwindow.h"
#include "container.h"

#include <QKeyEvent>
#include <QFocusEvent>
#include <QApplication>


FloatTextEdit::FloatTextEdit(QWidget *parent)
{
    this->setParent(parent);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setAutoFillBackground(true);

    selected = new bool(false);
}


FloatTextEdit::~FloatTextEdit()
{
    this->parentWidget()->close();
    this->close();
}


void FloatTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete && *selected)
    {
        Container *parent = qobject_cast<Container*>(this->parent());
        parent->close();
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

    Container *parent = qobject_cast<Container*>(this->parent());
    parent->setStyleSheet
            (
                "Container "
                "{"
                    "border-width : 2px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : rgb(225, 225, 225);"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"

                "Container:hover"
                "{"
                    "border-width : 2px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : rgb(225, 225, 225);"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"
            );
}


void FloatTextEdit::focusOutEvent(QFocusEvent *event)
{
    if (this->toPlainText() == "" || this->toPlainText() == "Blank Note")
    {
        this->close();
    }


    *selected = false;

    QTextCursor cursor= this->textCursor();
    cursor.clearSelection();
    this->setTextCursor(cursor);

    Container *parent = qobject_cast<Container*>(this->parent());
    parent->setStyleSheet
            (
                "Container "
                "{"
                    "border-width : 0px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : none;"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"

                "Container:hover"
                "{"
                    "border-width : 2px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : rgb(225, 225, 225);"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"
            );
}


void FloatTextEdit::enterEvent(QEvent *event)
{
    this->setCursor(Qt::IBeamCursor);
}


void FloatTextEdit::leaveEvent(QEvent *event)
{

}


void FloatTextEdit::fontSizeUp()
{

}

void FloatTextEdit::fontSizeDown()
{

}
