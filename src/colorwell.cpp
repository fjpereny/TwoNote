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


#include "colorwell.h"
#include <QSizePolicy>
#include <QString>
#include <QStyle>
#include <QPainter>
#include <iostream>


ColorWell::ColorWell(QWidget *parent, const QColor &color)
{
    this->color = new QColor;
    this->setFixedSize(20, 20);
//    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setColor(color);
}


ColorWell::~ColorWell()
{
    delete this->color;
}


void ColorWell::setColor(const QColor &color)
{
    const QString r = QString::number(color.red());
    const QString g = QString::number(color.green());
    const QString b = QString::number(color.blue());
    const QString styleSheet = QString
            (
                "border-width: 1px;"
                "border-color: rgb(226, 228, 231);"
                "border-style: solid;"
                "background-color: rgb(%1, %2, %3);"
            ).arg(r, g, b);
    this->setStyleSheet(styleSheet);
    *this->color = color;
}


QColor ColorWell::getColor()
{
    return *this->color;
}


