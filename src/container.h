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

#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include <QFrame>


//! Visible frame for all objects contained on the note page.
/*!
 *   The container acts as a frame and allows the user to move, resize and control the object
 *   that it contains.
*/
class Container : public QFrame
{
    Q_OBJECT

public:
    Container(QWidget *parent = nullptr);           //!< Default donstructor
    ~Container();                                   //!< Default destructor.

    void setMovable(bool);                          //!< Set this container as movable or immovable.
    bool getMovable();                              //!< Check if this container is currently movable.
    void setSizable(bool);                          //!< Set this container as resizable or fixed size.
    bool getSizable();                              //!< Check if this container is currently resizable.

private:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    bool *isMovable;
    bool *isSizable;
    int *clickOffsetX;
    int *clickOffsetY;
    int *clickPointX;
    int *clickPointY;
    int *startingWidth;
    int *startingHeight;
    int *currentPositionX;
    int *currentPositionY;
    QFrame *movePreviewFrame;

private slots:


signals:

};

#endif // CONTAINER_H
