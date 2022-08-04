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


#include "container.h"
#include "floattextedit.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabmainwidget.h"

#include <iostream>
#include <QObject>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QApplication>
#include <QScrollBar>
#include <QTextList>


FloatTextEdit::FloatTextEdit(QWidget *parent)
{
    this->window = qobject_cast<MainWindow*>(QApplication::activeWindow());

    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setAutoFillBackground(true);

    int marginTop = 15;
    int marginSides = 15;
    this->setFixedHeight(parent->height() - marginTop);
    this->setFixedWidth(parent->width() - marginSides);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setWordWrapMode(QTextOption::NoWrap);

    this->setFont(window->getCurrentFont());
    this->setCurrentFont(window->getCurrentFont());
    this->setTextColor(this->window->getCurrentTextColor());
    this->setCursor(Qt::IBeamCursor);
    this->setText("Blank Note");
    this->selectAll();
    this->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    selected = new bool(false);

    QObject::connect(this, &QTextEdit::textChanged, this, &FloatTextEdit::changeParentCursor);
    QObject::connect(this, &QTextEdit::textChanged, this, &FloatTextEdit::autoResize);
    QObject::connect(this, &QTextEdit::cursorPositionChanged, this, &FloatTextEdit::cursorSizeChange);
}


FloatTextEdit::~FloatTextEdit()
{
    if (this->window->getCurrentObject() == this)
    {
        this->window->setCurrentObject(nullptr);
    }

    if (this->parent())
    {
        this->parentWidget()->close();
    }
}


void FloatTextEdit::setupFont()
{
    this->setCurrentFont(this->window->getCurrentFont());
    this->setTextColor(this->window->getCurrentTextColor());
}


void FloatTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Insert)
    {
        this->setOverwriteMode(!this->overwriteMode());
        this->cursorSizeChange();
    }
    else if (event->key() == Qt::Key_Escape)
    {
        QTextCursor textCursor = this->textCursor();
        textCursor.clearSelection();
        this->setTextCursor(textCursor);
        this->clearFocus();
        this->parentWidget()->clearFocus();
        this->setCursorWidth(0);
    }
    else if (event->key() == Qt::Key_Tab)
    {
        QTextCursor cursor = this->textCursor();
        if (cursor.currentList())
        {
            QTextListFormat format = cursor.currentList()->format();
            format.setIndent(format.indent() + 1);
            cursor.createList(format);
        }
        else
        {
            QTextListFormat listFormat;
            listFormat.setStyle(QTextListFormat::ListStyleUndefined);
            cursor.createList(listFormat);
        }
    }
    else if (event->key() == Qt::Key_Backtab)
    {
        QTextCursor cursor = this->textCursor();
        QTextListFormat format = cursor.currentList()->format();
        if (format.indent() > 0)
        {
            format.setIndent(format.indent() - 1);
        }
        cursor.createList(format);
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}


void FloatTextEdit::cursorSizeChange()
{
    if (this->overwriteMode())
    {
        QFontMetrics metrics(this->currentFont());
        int curPos = this->textCursor().position();
        QString curText = this->toPlainText();
        int curCharWidth;
        if (curPos >= 0 && curPos < curText.length())
        {
            QChar curChar = curText[curPos];
            curCharWidth = metrics.boundingRect(curChar).width();
        }
        else
        {
            curCharWidth = metrics.averageCharWidth();
        }
        this->setCursorWidth(curCharWidth);
    }
    else
    {
        this->setCursorWidth(1);
    }
    this->update();
}


void FloatTextEdit::autoResize()
{
    while (this->horizontalScrollBar()->isVisible())
    {
        this->setFixedWidth(this->width() + 2);
    }

    while (this->verticalScrollBar()->isVisible())
    {
        this->setFixedHeight(this->height() + 2);
    }

    int marginTop = 15;
    int marginSides = 15;
    if (this->width())
    {
        if (this->width() > (this->parentWidget()->width() - marginSides))
        {
            this->parentWidget()->setFixedWidth(this->width() + marginSides);
        }
    }
    if (this->height() > (this->parentWidget()->height() - marginTop))
    {
        this->parentWidget()->setFixedHeight(this->height() + marginTop);
    }
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

    int curFontSize = this->currentFont().pointSize();
    QString fontSize = QString::number(curFontSize);
    QString fontSizeName = fontSize + " pt";
    win->getUi()->fontSizeComboBox->setCurrentText(fontSizeName);

    QFont font = win->getCurrentFont();
    font.setPointSize(curFontSize);
    win->setCurrentFont(font);
}


void FloatTextEdit::focusOutEvent(QFocusEvent *event)
{
    if (this->toPlainText() == "")
    {        
        Container *parent = qobject_cast<Container*>(this->parent());
        if (!parent->hasFocus())
            parent->close();
    }

    *selected = false;

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

    QWidget *focusedWidget = QApplication::focusWidget();
    if (focusedWidget)
    {
        Container *container = qobject_cast<Container*>(focusedWidget);
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(focusedWidget);
        if (container)
        {
            if (container != this->parent())
            {
                QTextCursor cursor = this->textCursor();
                cursor.clearSelection();
                this->setTextCursor(cursor);
            }
        }
        else if (textEdit)
        {
            QTextCursor cursor = this->textCursor();
            cursor.clearSelection();
            this->setTextCursor(cursor);
        }
    }
}


void FloatTextEdit::enterEvent(QEvent *event)
{
    this->cursorSizeChange();
}


void FloatTextEdit::leaveEvent(QEvent *event)
{
    this->setCursorWidth(0);
}


void FloatTextEdit::changeParentCursor()
{
    Container *parent = qobject_cast<Container*>(this->parent());
    parent->setCursor(Qt::IBeamCursor);
}

