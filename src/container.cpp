/*
 * Copyright (C) 2022 Frank Pereny
 *
 * This file is part of TwoNote <https://github.com/fjpereny/TwoNote>.
 *
 * TwoNote is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * TwoNote is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Foobar.
 * If not, see <https://www.gnu.org/licenses/>.
*/


#include "src/container.h"
#include "src/floattextedit.h"
#include "src/mainwindow.h"

#include <iostream>
#include <QMouseEvent>


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

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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
    this->isSizable = new bool(false);
    this->clickOffsetX = new int(0);
    this->clickOffsetY = new int(0);
    this->clickPointX = new int(0);
    this->clickPointY = new int(0);
    this->startingWidth = new int;
}


Container::~Container()
{    
    QWidget *winWidget = QWidget::window();
    MainWindow *win = qobject_cast<MainWindow*>(winWidget);
    if (win->getCurrentContainer() == this)
    {
        win->setCurrentContainer(nullptr);
    }
}


void Container::setMovable(bool b)
{
    *this->isMovable = b;
}

bool Container::getMovable()
{
    return *this->isMovable;
}


void Container::setSizable(bool b)
{
    *this->isSizable = b;
}

bool Container::getSizable()
{
    return *this->isSizable;
}


void Container::focusInEvent(QFocusEvent *event)
{
    QWidget *winWidget = QWidget::window();
    MainWindow *win = qobject_cast<MainWindow*>(winWidget);
    win->setCurrentContainer(this);
    QWidget *child = this->findChild<QWidget*>();
    win->setCurrentObject(child);

    this->setStyleSheet
            (
                "Container "
                "{"
                    "border-width : 2px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : rgb(200, 200, 200);"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"

                "Container:hover"
                "{"
                    "border-width : 2px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : rgb(200, 200, 200);"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"
            );
}


void Container::focusOutEvent(QFocusEvent *event)
{
    this->setStyleSheet
            (
                "Container "
                "{"
                    "border-width : 2px;"
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


void Container::mouseMoveEvent(QMouseEvent *event)
{
    int x, y;
    x = event->position().x();
    y = event->position().y();

    int grabSizeV = 15;
    int grabSizeH = 5;
    int minVPixels = grabSizeV;
    int maxHPixels = this->width() - grabSizeH;

    if (y <= minVPixels)
    {
           this->setCursor(Qt::SizeAllCursor);
    }
    else if (x >= maxHPixels)
    {
        this->setCursor(Qt::SizeHorCursor);
    }
    else
    {
        this->setCursor(Qt::IBeamCursor);
    }

    if (this->hasFocus() && this->getMovable())
    {
        int curX = this->pos().x();
        int curY = this->pos().y();

        this->move(curX + event->position().x() - *this->clickOffsetX, curY + event->position().y() - *this->clickOffsetY);
    }
    else if (this->hasFocus() && this->getSizable())
    {
        int moveX = event->globalPosition().x() - *this->clickPointX;
        int newWidth = *this->startingWidth + moveX;
        if (newWidth < 200)
        {
            newWidth = 200;
        }
        this->setFixedWidth(newWidth);
    }
}


void Container::mousePressEvent(QMouseEvent *event)
{
    int x, y;
    x = event->position().x();
    y = event->position().y();

    int grabSize = 15;
    int minVPixels = grabSize;
    int maxHPixels = this->width() - grabSize;

    if (y <= minVPixels)
    {
        this->setMovable(true);
        *this->clickOffsetX = x;
        *this->clickOffsetY = y;
    }
    else if (x >= maxHPixels)
    {
        this->setSizable(true);
        *this->clickPointX = event->globalPosition().x();
        *this->clickPointY = event->globalPosition().y();
        *this->startingWidth = this->width();
    }
}

void Container::mouseReleaseEvent(QMouseEvent *event)
{
    this->setMovable(false);
    this->setSizable(false);

//    Snapping position by pixel location
    int snapPixelSize = 30; // Set to even number to ensure proper rouding (division by 2)
    int newX, newY, gapX, gapY;

    gapX = this->pos().x() % snapPixelSize;
    gapY = this->pos().y() % snapPixelSize;

    if (gapX <= snapPixelSize / 2)
        newX = this->pos().x() - gapX;
    else
        newX = this->pos().x() + gapX;

    if (gapY <= snapPixelSize / 2)
        newY = this->pos().y() - gapY;
    else
        newY = this->pos().y() + gapY;

    this->move(newX, newY);
}


void Container::keyPressEvent(QKeyEvent *event)
{
    if (this->hasFocus())
    {
        if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
        {
            this->close();
        }
    }
}


