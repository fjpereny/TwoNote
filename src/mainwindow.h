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
#include <QListWidget>
#include <QTextDocument>
#include <QColorDialog>
#include "container.h"
#include "contextmenu.h"
#include "colordropdownmenu.h"

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

    Ui::MainWindow* getUi();

    void setCurrentFont(QFont font);
    QFont getCurrentFont();
    void setCurrentTextColor(const QColor color);
    QColor getCurrentTextColor();
    void setTextDialogColor(const QColor color);
    QColor getTextDialogColor();
    QFont getFormatPainterFont();

public slots:
    void hideAllContextMenus();

private slots:
    void keyPressEvent(QKeyEvent *event);
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
    void on_deleteButton_clicked();
    void on_clearFormatButton_clicked();
    void on_copyButton_clicked();
    void on_indentButton_clicked();
    void on_outdentButton_clicked();
    void on_formatPainterButton_clicked();
    void on_styleListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void changeStyle(QListWidgetItem *current);
    void on_styleListWidget_itemClicked(QListWidgetItem *item);
    void on_fontColorButton_clicked();
    void on_expandFontColorButton_clicked();
    void focusInEvent(QFocusEvent *event);

private:

    Ui::MainWindow *ui;
    QTextDocument *document;
    QWidget *currentObject;
    Container *currentContainer;
    QWidget *copiedObject;

    bool *bold;
    bool *italic;
    bool *underline;
    bool *strike;

    QFont *currentFont;
    QFont *formatPainterFont;

    QColor *currentTextColor;
    QColor *currentBackgroundColor;
    QColor *currentHighlightColor;
    QColor *textColorDialogColor;
    QColor *backgroundColorDialogColor;
    QColor *highlighColorDialogColor;

    ColorDropDownMenu *colorDropDown;

};
#endif // MAINWINDOW_H
