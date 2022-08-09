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


#include "todolist.h"

#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QKeyEvent>

ToDoList::ToDoList(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    this->setLayout(layout);

    this->addNewRow();
}


ToDoList::~ToDoList()
{

}


void ToDoList::addNewRow()
{
    QHBoxLayout *row = new QHBoxLayout(this);
    this->layout()->addItem(row);

    QCheckBox *checkBox = new QCheckBox(this);
    checkBox->setChecked(false);
    checkBox->setText("");
    checkBox->setCursor(Qt::ArrowCursor);
    row->addWidget(checkBox);

    QTextEdit *textEdit = new QTextEdit(this);
    QFontMetrics metrics(textEdit->currentFont());
    int height = metrics.height() + 4;
    textEdit->setFixedHeight(height);
    textEdit->setCursor(Qt::IBeamCursor);
    row->addWidget(textEdit);
}


void ToDoList::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {

    }
}
