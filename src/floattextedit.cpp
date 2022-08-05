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
    this->mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());

    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setAutoFillBackground(true);

    int marginTop = 15;
    int marginSides = 15;
    this->setFixedHeight(parent->height() - marginTop);
    this->setFixedWidth(parent->width() - marginSides);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setWordWrapMode(QTextOption::NoWrap);

    this->setFont(mainWindow->getCurrentFont());
    this->setCurrentFont(mainWindow->getCurrentFont());
    this->setTextColor(this->mainWindow->getCurrentTextColor());
    this->setCursor(Qt::IBeamCursor);
    this->setText("Blank Note");
    this->selectAll();
    this->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    QObject::connect(this, &QTextEdit::textChanged, this, &FloatTextEdit::changeParentCursor);
    QObject::connect(this, &QTextEdit::textChanged, this, &FloatTextEdit::autoResize);
    QObject::connect(this, &QTextEdit::cursorPositionChanged, this, &FloatTextEdit::cursorSizeChange);
}


FloatTextEdit::~FloatTextEdit()
{
    if (this->mainWindow->getCurrentObject() == this)
    {
        this->mainWindow->setCurrentObject(nullptr);
    }
}


void FloatTextEdit::setupFont()
{
    this->setCurrentFont(this->mainWindow->getCurrentFont());
    this->setTextColor(this->mainWindow->getCurrentTextColor());
}


void FloatTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Insert)
    {
        this->setOverwriteMode(!this->overwriteMode());
        this->cursorSizeChange();
    }
    else if (event->key() == Qt::Key_Space)
    {
        this->zoom(2);
    }
    else if (event->key() == Qt::Key_Escape)
    {
        this->zoomOut(100);
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
    mainWindow->setCurrentObject(this);
    Container *parent = qobject_cast<Container*>(this->parent());
    mainWindow->setCurrentContainer(parent);
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
    QFont font = mainWindow->getCurrentFont();
    font.setPointSize(curFontSize);
    mainWindow->setCurrentFont(font);

    mainWindow->hideAllContextMenus();
}


void FloatTextEdit::focusOutEvent(QFocusEvent *event)
{
    Container *parent = qobject_cast<Container*>(this->parent());

    if (this->toPlainText() == "" && (!parent->hasFocus()))
    {
        parent->close();
        return;
    }

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


void FloatTextEdit::zoom(float scale)
{
    QTextCursor cursor = this->textCursor();
    cursor.setPosition(0);
    while(!cursor.atBlockEnd())
    {
        cursor.setPosition(cursor.position(), QTextCursor::MoveAnchor);
        cursor.setPosition(cursor.position() + 1, QTextCursor::KeepAnchor);
        QTextCharFormat format = cursor.charFormat();
        float newSize = format.fontPointSize() * scale;
        format.setFontPointSize(newSize);
        cursor.setCharFormat(format);
        cursor.clearSelection();
    }
}
