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


#ifndef FLOATIMAGE_H
#define FLOATIMAGE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include "container.h"

class FloatImage : public QLabel
{
    Q_OBJECT
public:
    explicit FloatImage(QWidget *parent = nullptr);
    ~FloatImage();

    void setImage(QString imgPath);
    QImage getImage();

signals:

private:
    Container *container;

};

#endif // FLOATIMAGE_H
