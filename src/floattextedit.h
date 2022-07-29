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


#ifndef FLOATTEXTEDIT_H
#define FLOATTEXTEDIT_H

#include <QTextEdit>
#include <src/mainwindow.h>

class FloatTextEdit : public QTextEdit
{
public:
    FloatTextEdit(QWidget *parent = nullptr);
    ~FloatTextEdit();

    void setupFont();
    void autoResize();

    bool *selected;

private:
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    MainWindow *window;

signals:


private slots:
    void changeParentCursor();
};

#endif // FLOATTEXTEDIT_H
