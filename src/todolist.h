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


#ifndef TODOLIST_H
#define TODOLIST_H


#include <QObject>
#include <QWidget>


class ToDoList : public QWidget
{
    Q_OBJECT
public:
    ToDoList(QWidget *parent = nullptr);
    ~ToDoList();

    void addNewRow();

signals:

private:


private slots:
        void keyPressEvent(QKeyEvent *event);

};

#endif // TODOLIST_H
