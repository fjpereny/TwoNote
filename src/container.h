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

#ifndef CONTAINER_H
#define CONTAINER_H


#include <QWidget>
#include <QFrame>


class MainWindow;

//! Visible frame for all objects contained on the note page.
/*!
 *   The container acts as a frame and allows the user to move, resize and control the object
 *   that it contains.
*/
class Container : public QFrame
{
    Q_OBJECT

public:
    //! Default constructor.
    /*!
     * \brief Container::Container
     * \param parent
     */
    Container(QWidget *parent = nullptr);
    //! Default destructor.
    /*!
     * \brief Container::~Container
     */
    ~Container();

    //! Set this Container as movable during a mouse move event.
    /*!
     * \param bool b - True if movable, false if not movable.
     * \sa Container::getMovable
     */
    void setMovable(bool);

    //! Check if this Container is currently movable by a mouse move event.
    /*!
     * \return Returns true if this container is currently able to be moved.
     * \sa Container::setMovable, Container::isMovable
     */
    bool getMovable();

    //! Set this Container as resizable during a mouse move event.
    /*!
     * \brief Container::setSizable
     * \param bool b - True if resizable, false if fixed-size.
     * \sa Container::getSizable
     */
    void setSizable(bool);

    //! Check if this Container is currently resizable by a mouse move event.
    /*!
     * \brief Container::getSizable
     * \return Returns true if this container is currently sizable.
     * \sa Container::setSizable
     */
    bool getSizable();

private:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    //! Toggles Container movable or fixed.
    /*!
     * \brief True if this container is movable, false if fixed position.  Used to toggle movement for this
     * Container during a Container::mouseMoveEvent.
     * \sa Container::setMovable, Container::getMovable
     */
    bool *isMovable;

    //! Toggles Container resizable or fixed.
    /*!
     * \brief True if this container is sizable, false if fixed size.
     * \sa Container::setSizable, Container::getSizable
     */
    bool *isSizable;

    //! Stores x coordinate offset during a Container::mousePressEvent
    /*!
     * \brief Stores the offset between the Container x coordinate and the x coordinate of the location
     * where the mouse was pressed.  This is used to calculate the offset during a Container::mouseMoveEvent
     * resizing or movement operation.
     * \sa Container::mousePressEvent, Container::mouseMoveEvent
     */
    int *clickOffsetX;

    //! Stores y coordinate offset during a Container::mousePressEvent
    /*!
     * \brief Stores the offset between the Container y coordinate and the x coordinate of the location
     * where the mouse was pressed.  This is used to calculate the offset during a Container::mouseMoveEvent
     * resizing or movement operation.
     * \sa Container::mousePressEvent, Container::mouseMoveEvent
     */
    int *clickOffsetY;

    //! Stores x coordinate of mouse press during a Container::mousePressEvent
    /*!
     * \brief Stores the x coordinate of the location where the mouse was pressed.  This is
     * used to calculate resizing or movement operations.
     * \sa Container::mousePressEvent, Container::mouseMoveEvent
     */
    int *clickPointX;

    //! Stores y coordinate of mouse press during a Container::mousePressEvent
    /*!
     * \brief Stores the y coordinate of the location where the mouse was pressed.  This is
     * used to calculate resizing or movement operations.
     * \sa Container::mousePressEvent, Container::mouseMoveEvent
     */
    int *clickPointY;

    //! The width of the Container prior to a resizing ore movement operation.
    /*!
     * \brief The width of the Container just prior to a resizing ore movement operation.
     * This is used for calculating resizing and movement during a Container::mouseMoveEvent.
     * \sa Container::mousePressEvent, Container::mouseMoveEvent
     */
    int *startingWidth;

    //! The height of the Container just prior to a resizing ore movement operation.
    /*!
     * \brief The height of the Container just prior to a resizing ore movement operation.
     * This is used for calculating resizing and movement during a Container::mouseMoveEvent.
     * \sa Container::mousePressEvent, Container::mouseMoveEvent
     */
    int *startingHeight;

    //! The x coordinate of the Container just prior to a resizing ore movement operation.
    /*!
     * \brief The x coordinate of the Container just prior to a resizing ore movement operation.
     * This is used for calculating resizing and movement during a Container::mouseMoveEvent.
     * \sa Container::mousePressEvent, Container::mouseMoveEvent
     */
    int *currentPositionX;

    //! The y coordinate of the Container just prior to a resizing ore movement operation.
    /*!
     * \brief The y coordinate of the Container just prior to a resizing ore movement operation.
     * This is used for calculating resizing and movement during a Container::mouseMoveEvent.
     * \sa Container::mousePressEvent, Container::mouseMoveEvent
     */
    int *currentPositionY;

    //! A QFrame object used for movement and resizing preview purposes.
    /*!
     * \brief This object is instantiated during a movement or resizing operation to show the user
     * a preview of the new location or size of the Container.  This object is used for visual
     * purposes only and should be destroyed once the relevent operation is completed.
     *
     */
    QFrame *movePreviewFrame;

    //! A pointer to the MainWindow object of this application instance.
    /*!
     * \brief This is used to access the MainWindow instance and allows this Container to access
     * public methods, variables and other GUI objects of the application.
     *
     */
    MainWindow *mainWindow;

private slots:


signals:

};

#endif // CONTAINER_H
