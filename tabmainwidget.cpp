#include "tabmainwidget.h"
#include "floattextedit.h"
#include "notetabwidget.h"
#include "container.h"

#include <QMouseEvent>
#include <iostream>
#include <QWidget>
#include <QHBoxLayout>

TabMainWidget::TabMainWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setParent(parent);
    this->setCursor(Qt::IBeamCursor);

    clicked_x = nullptr;
    clicked_y = nullptr;
    createEnabled = new bool(true);
    createMode = new QString("TextEdit");
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

    if (!this->childAt(event->pos()))
    {
        Container *newContainer = new Container(this);
        newContainer->move(*this->clicked_x - 20, *this->clicked_y - 20);
        QHBoxLayout *newContainerLayout = new QHBoxLayout(newContainer);
        newContainerLayout->setContentsMargins(0, 0, 0, 0);
        newContainer->setLayout(newContainerLayout);
        newContainer->show();

        if (createMode)
        {
            if (*createMode == "TextEdit")
            {
                FloatTextEdit *newTextEdit = new FloatTextEdit(newContainer);
                newContainerLayout->addWidget(newTextEdit);
                newTextEdit->setText("Blank Note");
                newTextEdit->selectAll();
                newTextEdit->setFontPointSize(12);
                newTextEdit->setFontFamily("DejaVu Sans");
                newTextEdit->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
                newTextEdit->setTextColor(Qt::black);
                newTextEdit->show();
                newTextEdit->setFocus();

            }
        }
    }
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
