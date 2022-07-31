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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "container.h"
#include "contextmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCurrentContainer(Container* container = nullptr);
    Container* getCurrentContainer();
    void setCurrentObject(QWidget* object = nullptr);
    QWidget* getCurrentObject();

    int getFontSize();
    QString getFontFamily();
    bool getBold();
    bool getItalic();
    bool getUnderline();
    bool getStrike();

    static MainWindow* getMainWindow();
    Ui::MainWindow* getUi();

    void setCurrentFont(QFont font);
    QFont getCurrentFont();

    QColor getCurrentTextColor();

private slots:
    void on_ribbonBar_currentChanged(int index);
    void on_tabWidget_tabBarDoubleClicked(int index);
    void setTabText();
    void on_tabWidget_tabBarClicked(int index);
    void on_boldButton_clicked();
    void on_italicButton_clicked();
    void on_underlineButton_clicked();
    void on_strikeButton_clicked();
    void on_fontSizeComboBox_currentIndexChanged(int index);
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_bulletsButton_clicked();

    void on_numberingButton_clicked();

    void on_exitButton_clicked();

    void on_printButton_clicked();

private:
    Ui::MainWindow *ui;
    QWidget *currentObject;
    Container *currentContainer;

    // Application States
    bool *bold;
    bool *italic;
    bool *underline;
    bool *strike;
    QFont *currentFont;
    QColor *currentTextColor;
};
#endif // MAINWINDOW_H
