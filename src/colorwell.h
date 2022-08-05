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


#ifndef COLORWELL_H
#define COLORWELL_H


#include <QFrame>
#include <QObject>
#include <QWidget>
#include "mainwindow.h"


//! Color container for dialogs and context menus.
/*!
 *   Acts as a container for a QColor that can be uased for color selection
 *   dialogs and context menus.
*/
class ColorWell : public QFrame
{
    Q_OBJECT

public:
    //! Default constructor.
    /*!
     * \brief Default constructor will create a white 20px by 20px ColorWell.
     * \param QWidget *parent - Parent widget
     * \param const QColor &color - Color of the ColorWell
     */
    ColorWell(QWidget *parent = nullptr, const QColor &color = Qt::white);

    //! Default destructor.
    ~ColorWell();


    //! Sets the color of this ColorWell.
    /*!
     * \param const QColor &color - The new color for this ColorWell.
     * \sa ColorWell::getColor, ColorWell::color
     */
    void setColor(const QColor color);

    //! Gets the color of this ColorWell.
    /*!
     * \return The current color of this ColorWell.
     * \sa ColorWell::setColor, ColorWell::color
     */
    QColor getColor();

private:
    //! The color of this ColorWell.
    /*!
     * \sa ColorWell::setColor, ColorWell::getColor
     */
    QColor *color;

    //! Pointer to the MainWindow of the application.
    /*!
     * \sa MainWindow::MainWindow
     */
    MainWindow *mainWindow;

private slots:
    void mousePressEvent(QMouseEvent *event);
};

#endif // COLORWELL_H
