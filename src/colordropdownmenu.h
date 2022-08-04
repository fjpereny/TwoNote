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


#ifndef COLORDROPDOWNMENU_H
#define COLORDROPDOWNMENU_H


#include <QWidget>
#include <QFrame>


class MainWindow;



class ColorDropDownMenu : public QFrame
{
    Q_OBJECT

public:
    ColorDropDownMenu(QWidget *parent = nullptr);
    ~ColorDropDownMenu();

private:

    MainWindow *mainWindow;

signals:

private slots:
    void leaveEvent(QEvent *event);
    void openColorDialog();
};

#endif // COLORDROPDOWNMENU_H
