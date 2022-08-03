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
#include <mainwindow.h>


//! Floating rich text editor.
/*!
 *  Rich text editor for writing notes contained within a Container.
*/
class FloatTextEdit : public QTextEdit
{
public:
    //! Default constructor.
    /*!
     * \brief FloatTextEdit::FloatTextEdit
     * \param parent
     */
    FloatTextEdit(QWidget *parent = nullptr);

    //! Default destructor.
    /*!
     * \brief FloatTextEdit::~FloatTextEdit
     * \param parent
     */
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

    void cursorSizeChange();
    MainWindow *window;

signals:

private slots:
    //! Changes the parent Container mouse cursor to IBeam cursor.
    /*!
     * \brief If the mouse is hovering the Container during a text change event (typing)
     * the cursor will change to an IBeam style cursor to reflect the user is actively typing.
     * This also makes the mouse pointer less distracting while typing.
     * \sa FloatTextEdit::cursorSizeChange()
     */
    void changeParentCursor();
};

#endif // FLOATTEXTEDIT_H
