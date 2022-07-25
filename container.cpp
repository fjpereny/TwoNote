#include "container.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QHBoxLayout>

#include <iostream>


Container::Container(QWidget *parent)
    : QFrame{parent}
{
    this->setParent(parent);
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    this->setMinimumWidth(200);
    this->setMinimumHeight(100);

    this->setStyleSheet
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

    this->setMouseTracking(true);
}


Container::~Container()
{

}


void Container::focusInEvent(QFocusEvent *event)
{

}


void Container::focusOutEvent(QFocusEvent *event)
{

}


void Container::mouseMoveEvent(QMouseEvent *event)
{
    int x, y;
    x = event->position().x();
    y = event->position().y();

    int grabSize = 10;
    int minVPixels = grabSize;
    int maxHPixels = this->width() - grabSize;

    if (y <= minVPixels)
        this->setCursor(Qt::SizeAllCursor);
    else if (x >= maxHPixels)
        this->setCursor(Qt::SizeHorCursor);
    else
        this->setCursor(Qt::IBeamCursor);
}
