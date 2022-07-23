#include "tabmainwidget.h"
#include "floattextedit.h"
#include "notetabwidget.h"

#include <QMouseEvent>
#include <iostream>

TabMainWidget::TabMainWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setParent(parent);
    this->setCursor(Qt::ArrowCursor);

    clicked_x = nullptr;
    clicked_y = nullptr;
}

TabMainWidget::~TabMainWidget()
{

}

void TabMainWidget::mousePressEvent(QMouseEvent *event)
{
    if (clicked_x)
        *this->clicked_x = event->position().x();
    else
        this->clicked_x = new int(event->position().x());

    if (clicked_y)
        *this->clicked_y = event->position().y();
    else
        this->clicked_y = new int(event->position().y());

    FloatTextEdit *newTextEdit = new FloatTextEdit(this);

    newTextEdit->setText("Blank Note");
    newTextEdit->move(*this->clicked_x, *this->clicked_y);
    newTextEdit->setFixedWidth(200);
    newTextEdit->setFixedHeight(100);
    newTextEdit->selectAll();
    newTextEdit->show();
    newTextEdit->setFocus();
}

void TabMainWidget::keyPressEvent(QKeyEvent *event)
{

}

void TabMainWidget::focusInEvent(QFocusEvent *event)
{

}

void TabMainWidget::focusOutEvent(QFocusEvent *event)
{

}
