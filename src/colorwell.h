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


#ifndef COLORWELL_H
#define COLORWELL_H

#include <QFrame>
#include <QObject>
#include <QWidget>

class ColorWell : public QFrame
{
    Q_OBJECT

public:
    ColorWell(QWidget *parent = nullptr, const QColor &color = Qt::white);
    ~ColorWell();

    void setColor(const QColor &color);
    QColor getColor();

private:
    QColor *color;

};

#endif // COLORWELL_H
