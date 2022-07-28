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


#include "floattextedit.h"
#include "tabmainwidget.h"
#include "mainwindow.h"
#include "container.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QApplication>
#include <iostream>


FloatTextEdit::FloatTextEdit(QWidget *parent)
{
    this->setParent(parent);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setAutoFillBackground(true);

    int marginTop = 2;
    int marginSides = 10;
    this->setFixedHeight(parent->height() - marginTop);
    this->setFixedWidth(parent->width() - marginSides);

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);

    this->setCursor(Qt::IBeamCursor);
    this->setupFont();
    this->setText("Blank Note");
    this->selectAll();
    this->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    selected = new bool(false);

    QObject::connect(this, &QTextEdit::textChanged, this, &FloatTextEdit::changeParentCursor);
}


FloatTextEdit::~FloatTextEdit()
{
    QWidget *winWidget = QWidget::window();
    MainWindow *win = qobject_cast<MainWindow*>(winWidget);
    if (win->getCurrentObject() == this)
    {
        win->setCurrentObject(nullptr);
    }

    if (this->parent())
    {
        this->parentWidget()->close();
    }
}


void FloatTextEdit::setupFont()
{
    QWidget *winWidget = QWidget::window();
    MainWindow *win = qobject_cast<MainWindow*>(winWidget);
    QFont font = this->currentFont();
    font.setPointSize(win->getFontSize());
    font.setFamily("DejaVu Sans");
    font.setBold(win->getBold());
    font.setItalic(win->getItalic());
    font.setStrikeOut(false);
    this->setCurrentFont(font);
    this->setTextColor(Qt::black);
}


void FloatTextEdit::keyPressEvent(QKeyEvent *event)
{    
    QTextEdit::keyPressEvent(event);

    if (event->key() == Qt::Key_Insert)
    {
        this->setOverwriteMode(!this->overwriteMode());
    }

    this->setupFont();
}


void FloatTextEdit::focusInEvent(QFocusEvent *event)
{
    QWidget *winWidget = QWidget::window();
    MainWindow *win = qobject_cast<MainWindow*>(winWidget);
    win->setCurrentObject(this);

    Container *parent = qobject_cast<Container*>(this->parent());
    win->setCurrentContainer(parent);
    parent->setStyleSheet
            (
                "Container "
                "{"
                    "border-width : 2px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : rgb(200, 200, 200);"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"

                "Container:hover"
                "{"
                    "border-width : 2px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : rgb(200, 200, 200);"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"
            );


    QFont font = this->currentFont();
    font.setPointSize(win->getFontSize());
    this->setCurrentFont(font);
}


void FloatTextEdit::focusOutEvent(QFocusEvent *event)
{
    if (this->toPlainText() == "" || this->toPlainText() == "Blank Note")
    {        
        Container *parent = qobject_cast<Container*>(this->parent());
        if (!parent->hasFocus())
            parent->close();
    }

    *selected = false;

    QTextCursor cursor= this->textCursor();
    cursor.clearSelection();
    this->setTextCursor(cursor);

    Container *parent = qobject_cast<Container*>(this->parent());
    parent->setStyleSheet
            (
                "Container "
                "{"
                    "border-width : 2px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : none;"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"

                "Container:hover"
                "{"
                    "border-width : 2px;"
                    "border-style : solid;"
                    "border-radius : 0px;"
                    "border-color : rgb(225, 225, 225);"
                    "border-top-width : 15px;"
                    "background-color : none;"
                "}"
            );
}


void FloatTextEdit::enterEvent(QEvent *event)
{

}


void FloatTextEdit::leaveEvent(QEvent *event)
{

}


void FloatTextEdit::changeParentCursor()
{
    Container *parent = qobject_cast<Container*>(this->parent());
    parent->setCursor(Qt::IBeamCursor);
}


