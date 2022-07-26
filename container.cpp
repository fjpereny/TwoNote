#include "container.h"
#include "mainwindow.h"

#include <QMouseEvent>
#include <iostream>


Container::Container(QWidget *parent)
    : QFrame{parent}
{
    this->setParent(parent);
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    this->setFocusPolicy(Qt::ClickFocus);

    this->setMinimumWidth(200);
    this->setMinimumHeight(100);
    this->setMaximumWidth(16777215);
    this->setMaximumHeight(16777215);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setSizePolicy(sizePolicy);

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

    this->isMovable = new bool(false);
    this->clickOffsetX = new int;
    this->clickOffsetY = new int;
}


Container::~Container()
{

}


void Container::setMovable(bool b)
{
    *this->isMovable = b;
}

bool Container::getMovable()
{
    return *this->isMovable;
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

    int grabSize = 15;
    int minVPixels = grabSize;
    int maxHPixels = this->width() - grabSize;

    if (y <= minVPixels)
        this->setCursor(Qt::SizeAllCursor);
    else if (x >= maxHPixels)
        this->setCursor(Qt::SizeHorCursor);
    else
        this->setCursor(Qt::IBeamCursor);

    if (this->hasFocus() && this->getMovable())
    {
        int curX = this->pos().x();
        int curY = this->pos().y();

        this->move(curX + event->position().x() - *this->clickOffsetX, curY + event->position().y() - *this->clickOffsetY);
    }
}


void Container::mousePressEvent(QMouseEvent *event)
{
    int x, y;
    x = event->position().x();
    y = event->position().y();

    int grabSize = 15;
    int minVPixels = grabSize;

    if (y <= minVPixels)
    {
        this->setMovable(true);
        *this->clickOffsetX = x;
        *this->clickOffsetY = y;
    }
}

void Container::mouseReleaseEvent(QMouseEvent *event)
{
    this->setMovable(false);
}
