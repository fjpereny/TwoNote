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

#include <iostream>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QWidget>

TabMainWidget::TabMainWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setParent(parent);
    this->setCursor(Qt::IBeamCursor);

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
