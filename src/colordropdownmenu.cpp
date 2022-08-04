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
#include <QGridLayout>
#include <QFrame>
#include <QSizePolicy>
#include <QApplication>

ColorDropDownMenu::ColorDropDownMenu(QWidget* parent)
    : QFrame(parent)
{
    this->mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());

    this->setFixedWidth(200);
    this->setFixedHeight(500);
    this->setAutoFillBackground(true);

    QPalette palette;
    palette = parent->palette();
    palette.setBrush(QPalette::Window, Qt::white);
    this->setPalette(palette);

    QGridLayout layout;
    QFrame frameAutomatic;
    frameAutomatic.setFixedSize(20, 20);
    frameAutomatic.setAutoFillBackground(true);
    QFrame frameStandard;
    frameStandard.setFixedSize(20, 20);
    frameStandard.setAutoFillBackground(true);

    palette.setBrush(QPalette::Window, Qt::black);
    frameAutomatic.setPalette(palette);
    layout.addWidget(&frameAutomatic, 0, 0, Qt::AlignCenter);
}


ColorDropDownMenu::~ColorDropDownMenu()
{

}


void ColorDropDownMenu::focusOutEvent(QFocusEvent *event)
{
    this->hide();
}
