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


#include "container.h"
#include "floattextedit.h"
#include "floatimage.h"
#include "mainwindow.h"

#include <iostream>
#include <QMouseEvent>
#include <QStyle>


Container::Container(QWidget *parent)
    : QFrame{parent}
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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

    this->isMovable = new bool(false);
    this->isSizable = new bool(false);
    this->clickOffsetX = new int(0);
    this->clickOffsetY = new int(0);
    this->clickPointX = new int(0);
    this->clickPointY = new int(0);
    this->startingWidth = new int;
    this->startingHeight = new int;
    this->currentPositionX = new int(this->pos().x());
    this->currentPositionY = new int(this->pos().y());

    // Add scalar operatin to adjust while created during zoomed state.
    this->zoomPositionX = nullptr;
    this->zoomPositionX = nullptr;

    this->movePreviewFrame = nullptr;

    QWidget *winWidget = QWidget::window();
    MainWindow *window = qobject_cast<MainWindow*>(winWidget);
    if (window)
    {
        this->mainWindow = window;
    }
    else
    {
        std::cerr << "Error: Container::Container() could not get pointer to MainWindow.\n"
                     "\tthis->mainWindow set to nullptr and may have unexpected consequences.";
        this->mainWindow = nullptr;
    }
}


Container::~Container()
{
    delete this->isMovable;
    delete this->isSizable;
    delete this->clickOffsetX;
    delete this->clickOffsetY;
    delete this->clickPointX;
    delete this->clickPointY;
    delete this->startingWidth;
    delete this->startingHeight;
    delete this->currentPositionX;
    delete this->currentPositionY;
    delete this->movePreviewFrame;

    if (mainWindow)
    {
        if (mainWindow->getCurrentContainer() == this)
        {
            mainWindow->setCurrentContainer(nullptr);
        }
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

    QWidget *child = this->findChild<QWidget*>();
    if (!child->hasFocus())
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(child);
        if (textEdit)
        {
            QTextCursor cursor = textEdit->textCursor();
            cursor.clearSelection();
            textEdit->setTextCursor(cursor);
        }
    }
}


void Container::mouseMoveEvent(QMouseEvent *event)
{    
    QWidget *child = this->findChild<QWidget*>();
    FloatImage *floatImage = qobject_cast<FloatImage*>(child);

    int x, y;
    x = event->position().x();
    y = event->position().y();

    int grabSizeV = 10;
    int grabSizeH = 10;
    int minVPixels = grabSizeV;
    int maxHPixels = this->width() - grabSizeH;
    int maxVPixels = this->height() - grabSizeV;

    if (y <= minVPixels)
    {
        this->setCursor(Qt::SizeAllCursor);
    }    
    else if (floatImage && y >= maxVPixels && x >= maxHPixels)
    {
        this->setCursor(Qt::SizeFDiagCursor);
    }
    else if (floatImage && y >= maxVPixels)
    {
        this->setCursor(Qt::SizeVerCursor);
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
        int newX = curX + event->position().x() - *this->clickOffsetX;
        int newY = curY + event->position().y() - *this->clickOffsetY;

    //  Snapping position by pixel location
        int snapPixelSize = 20; // Set to even number to ensure proper rouding (division by 2)
        int gapX = newX % snapPixelSize;
        int gapY = newY % snapPixelSize;

        if (gapX < snapPixelSize / 2)
            newX -= gapX;
        else
            newX = newX + snapPixelSize - gapX;

        if (gapY <= snapPixelSize / 2)
            newY -= gapY;
        else
            newY = newY + snapPixelSize - gapY;
        this->move(newX, newY);

        // Move preview position
        if (!this->movePreviewFrame)
        {
            this->movePreviewFrame = new QFrame(this->parentWidget());
            this->movePreviewFrame->setStyleSheet
                    (
                        "border-width : 2px;"
                        "border-style : solid;"
                        "border-radius : 0px;"
                        "border-color : rgba(200, 200, 200, 100);"
                        "border-top-width : 15px;"
                        "background-color : none;"
                    );
            this->movePreviewFrame->setFixedWidth(this->width());
            this->movePreviewFrame->setFocusPolicy(Qt::NoFocus);
            this->movePreviewFrame->setFixedHeight(this->height());
            this->movePreviewFrame->move(*this->currentPositionX, *this->currentPositionY);
            this->movePreviewFrame->show();
        }
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
        QWidget *child = this->findChild<QWidget*>();
        if (child)
        {
            child->setFixedWidth(newWidth - 15);
        }

        FloatImage *floatImage = qobject_cast<FloatImage*>(child);
        if (floatImage)
        {
            int moveY = event->globalPosition().y() - *this->clickPointY;
            int newHeight = *this->startingHeight + moveY;
            this->setFixedHeight(newHeight);
            if (child)
            {
                child->setFixedHeight(newHeight - 30);
            }
        }
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
        *this->startingHeight = this->height();
    }

    *this->currentPositionX = this->pos().x();
    *this->currentPositionY = this->pos().y();
}


void Container::mouseReleaseEvent(QMouseEvent *event)
{
    this->setMovable(false);
    this->setSizable(false);

    *this->currentPositionX = this->pos().x();
    *this->currentPositionY = this->pos().y();

    if (this->movePreviewFrame)
    {
        this->movePreviewFrame->close();
        this->movePreviewFrame = nullptr;
    }

    FloatTextEdit *textEdit = this->findChild<FloatTextEdit*>();
    if (textEdit)
    {
        textEdit->autoResize();
    }
}


void Container::keyPressEvent(QKeyEvent *event)
{
    if (this->hasFocus())
    {
        if (event->key() == Qt::Key_Escape)
        {
            this->clearFocus();
        }
        else if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace)
        {
            this->close();
        }
        else
        {
            this->findChild<QWidget*>()->setFocus();
        }
    }
}


int Container::getZoomX()
{
    if (!this->zoomPositionX)
    {
        this->zoomPositionX = new int(this->pos().x());
    }
    return *this->zoomPositionX;
}

int Container::getZoomY()
{
    if(!this->zoomPositionY)
    {
        this->zoomPositionY = new int(this->pos().y());
    }
    return *this->zoomPositionY;
}


void Container::moveEvent(QMoveEvent *event)
{
    // Check to keep Containers in bounds.
    int x = event->pos().x();
    int y = event->pos().y();
    if (x < 0 || y < 0)
    {
        if (x < 0)
        {
            x = 0;
        }
        if (y < 0)
        {
            y = 0;
        }
        this->move(x, y);
    }

    std::cout << event->pos().x() << std::endl;
    std::cout << event->pos().y() << std::endl;
//    if (!this->zoomPositionX)
//    {
//        this->zoomPositionX = new int(event->pos().x());
//    }
//    else
//    {
//        *this->zoomPositionX = event->pos().x();
//    }

//    if (!this->zoomPositionY)
//    {
//        this->zoomPositionY = new int(event->pos().y());
//    }
//    else
//    {
//        *this->zoomPositionY = event->pos().y();
//    }
}
