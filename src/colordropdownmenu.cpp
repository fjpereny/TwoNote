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


#include "colordropdownmenu.h"
#include "mainwindow.h"
#include "colorwell.h"
#include <QGridLayout>
#include <QFrame>
#include <QSizePolicy>
#include <QApplication>
#include <QLabel>

ColorDropDownMenu::ColorDropDownMenu(QWidget* parent)
    : QFrame(parent)
{
    this->mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());

    this->setFixedWidth(250);
    this->setFixedHeight(400);
    this->setAutoFillBackground(true);
    this->setStyleSheet
            (
                "ColorDropDownMenu"
                "{"
                "color: rgb(0, 0, 0);"
                "background-color: rgb(255, 255, 255);"
                "border-width : 1px;"
                "border-style : solid;"
                "border-radius : 0px;"
                "border-color : rgb(0, 0, 0);"
                "}"

                "QLabel"
                "{"
                "color: rgb(0, 0, 0);"
                "}"
            );

    QGridLayout *layout = new QGridLayout(this);
    this->setLayout(layout);

    ColorWell *automatic = new ColorWell(this, Qt::black);
    automatic->setFixedSize(30, 30);
    layout->addWidget(automatic, 0, 0);

    QLabel *automaticText = new QLabel(this);
    automaticText->setText("Automatic");
    layout->addWidget(automaticText, 0, 1);

    ColorWell *blue = new ColorWell(this, Qt::blue);
    blue->setColor(Qt::red);
    layout->addWidget(blue, 1, 1);
}


ColorDropDownMenu::~ColorDropDownMenu()
{

}


void ColorDropDownMenu::leaveEvent(QEvent *event)
{
    this->hide();
}
