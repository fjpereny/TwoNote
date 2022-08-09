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


#include <vector>
#include <QTextEdit>
#include "mainwindow.h"
#include "tabmainwidget.h"
#include "container.h"


//! Floating rich text editor.
/*!
 *  \image html FloatTextEdit.png
 *  Rich text editor for writing notes contained within a Container.
*/
class FloatTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    //! Default constructor.
    /*!
     * \param parent
     */
    FloatTextEdit(QWidget *parent = nullptr);

    //! Default destructor.
    /*!
     * \brief Destruction of this object will trigger destruction of the parent Container
     * object.  If the MainWindow::currentObject is this object, it will set the
     * MainWindow::currentObject to a nullptr.
     */
    ~FloatTextEdit();

    //! Resizes this object based on the contents (text size).
    /*!
     * \brief This function is used to automatically resize and enlarge this widget to
     * match the contents as the user types, pastes or modifies data contained within.
     * \sa MainWindow::currentObject
     */
    void autoResize();


    void zoom(float scale);

private:
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    //! Sets the current font to the selected font of the MainWindow
    /*!
     * \brief This is used to keep the current font matching the options selected in the
     * MainWindow (Font Family, Color, etc.).
     */
    void setupFont();

    //! Changes the parent Container mouse cursor to IBeam cursor.
    /*!
     * \brief If the mouse is hovering the Container during a text change event (typing)
     * the cursor will change to an IBeam style cursor to reflect the user is actively typing.
     * This also makes the mouse pointer less distracting while typing.
     * \sa FloatTextEdit::cursorSizeChange()
     */
    void changeParentCursor();

    //! Changes the cursor with during overwrite mode (insert key pressed)
    /*!
     * \brief Changes the thickness of the text cursor if the insert key is pressed and overwrite
     * mode is initiated.  The cursor thickness will match the thickness of the QFontMetric for the
     * next character.  If at the end of the line, the cursor thickness will match the average
     * character thickness for the current font.
     * \sa FloatTextEdit::changeParentCursor()
     */
    void cursorSizeChange();


    bool *selected;

    //! A pointer to the MainWindow object of this application instance.
    /*!
     * \brief This is used to access the MainWindow instance and allows this Container to access
     * public methods, variables and other GUI objects of the application.
     *
     */
    MainWindow *mainWindow;
    Container *container;
    TabMainWidget *tabMainWidget;

    bool *allowPointSizeChanges;
    std::vector<float> *absolutePointSize;

signals:

private slots:
    void updatePointSizeVector();
    void wheelEvent(QWheelEvent *event);
};

#endif // FLOATTEXTEDIT_H
