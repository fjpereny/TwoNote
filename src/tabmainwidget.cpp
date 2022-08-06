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


#include "tabmainwidget.h"
#include "floattextedit.h"
#include "floatimage.h"
#include "notetabwidget.h"
#include "container.h"
#include "mainwindow.h"

#include <iostream>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QWidget>
#include <QSizePolicy>
#include <QApplication>


TabMainWidget::TabMainWidget(QWidget *parent)
    : QWidget{parent}
{    
    this->mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());

    this->zoomScale = new float(1.0);

    this->setCursor(Qt::IBeamCursor);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    clicked_x = nullptr;
    clicked_y = nullptr;
    createEnabled = new bool(true);
    createMode = new QString("TextEdit");
//    createMode = new QString("FloatImage");

    contextMenu = new ContextMenu(this);
    contextMenu->hide();
}


TabMainWidget::~TabMainWidget()
{
    delete this->zoomScale;
    delete this->clicked_x;
    delete this->clicked_y;
    delete this->createEnabled;
    delete this->createMode;
    contextMenu->close();
}


void TabMainWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
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
                    newTextEdit->show();
                    newTextEdit->setFocus();
                }

                else if(*createMode == "FloatImage")
                {
                    FloatImage *floatImage = new FloatImage(newContainer);
                    newContainerLayout->addWidget(floatImage);
                    floatImage->setImage("test.jpg");
                    floatImage->show();
                    floatImage->setFocus();
                }
            }
        }

        if (contextMenu && !contextMenu->isHidden())
        {
            contextMenu->hide();
        }

    }
    else if (event->button() == Qt::RightButton)
    {
        if (!contextMenu)
        {
            this->contextMenu = new ContextMenu(this);
        }
        this->contextMenu->move(event->pos());
        this->contextMenu->show();
    }
}


float TabMainWidget::getZoomScale()
{
    return *this->zoomScale;
}


void TabMainWidget::setZoomScale(const float scale)
{
    *this->zoomScale = scale;
}


void TabMainWidget::zoomIn()
{
    if (*this->zoomScale < 10)
    {
        *this->zoomScale *= 1.05;
        this->zoomAllChildren(1.25);
    }
}


void TabMainWidget::zoomOut()
{
    if (*this->zoomScale > 0.25)
    {
        *this->zoomScale /= 1.05;
        this->zoomAllChildren(1.0 / 1.05);
    }
}


void TabMainWidget::zoomAllChildren(const float &scale)
{
    for (QObject *child : this->children())
    {
        Container* container = qobject_cast<Container*>(child);
        if (container)
        {
            int newX = container->getZoomX() * scale;
            int newY = container->getZoomY() * scale;
            container->move(newX, newY);

            FloatTextEdit *floatTextEdit = container->findChild<FloatTextEdit*>();
            if (floatTextEdit)
            {
                floatTextEdit->zoom(scale);
            }
        }
    }
}
