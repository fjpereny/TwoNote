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


#include "colordropdownmenu.h"
#include "mainwindow.h"
#include "colorwell.h"
#include <QGridLayout>
#include <QFrame>
#include <QSizePolicy>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>


ColorDropDownMenu::ColorDropDownMenu(QWidget* parent)
    : QFrame(parent)
{
    this->mainWindow = qobject_cast<MainWindow*>(QApplication::activeWindow());

    this->setFixedWidth(250);
    this->setFixedHeight(400);
    this->setAutoFillBackground(true);
    this->setStyleSheet
            (
                "ColorDropDownMenu"
                "{"
                "color: rgb(0, 0, 0);"
                "background-color: rgb(255, 255, 255);"
                "border-width : 1px;"
                "border-style : solid;"
                "border-radius : 0px;"
                "border-color : rgb(94, 94, 94);"
                "}"
            );

    QGridLayout *layout = new QGridLayout(this);
    this->setLayout(layout);

    QSize largeColorWell(30, 30);
    QSize smallColorWell(20, 20);

    // Row 0
    // Automatic Text
    ColorWell *automatic = new ColorWell(this, Qt::black);
    automatic->setFixedSize(largeColorWell);
    layout->addWidget(automatic, 0, 0, 1, 2);

    QLabel *automaticText = new QLabel(this);
    automaticText->setText("Automatic");
    layout->addWidget(automaticText, 0, 2, 1, 8);
    automaticText->setStyleSheet
            (
                "color: black;"
            );

    // Row 1
    QLabel *themeColorsLabel = new QLabel(this);
    themeColorsLabel->setText("  Theme Colors");
    themeColorsLabel->setMaximumHeight(30);
    layout->addWidget(themeColorsLabel, 1, 0, 1, 10);
    themeColorsLabel->setStyleSheet
            (
            "color: rgb(94, 94, 94);"
            "font-weight: bold;"
            "background-color: rgb(235, 235, 235);"
            );

    // Row 2
    ColorWell *white= new ColorWell(this, Qt::white);
    white->setFixedSize(smallColorWell);
    layout->addWidget(white, 2, 0, 1, 1);
    ColorWell *black= new ColorWell(this, Qt::black);
    black->setFixedSize(smallColorWell);
    layout->addWidget(black, 2, 1, 1, 1);
    ColorWell *lightGray = new ColorWell(this, QColor(231, 230, 230));
    lightGray->setFixedSize(smallColorWell);
    layout->addWidget(lightGray, 2, 2, 1, 1);
    ColorWell *blueGray = new ColorWell(this, QColor(68, 84, 106));
    blueGray->setFixedSize(smallColorWell);
    layout->addWidget(blueGray, 2, 3, 1, 1);
    ColorWell *blue = new ColorWell(this, QColor(91, 155, 213));
    blue->setFixedSize(smallColorWell);
    layout->addWidget(blue, 2, 4, 1, 1);
    ColorWell *orange = new ColorWell(this, QColor(237, 125, 49));
    orange->setFixedSize(smallColorWell);
    layout->addWidget(orange, 2, 5, 1, 1);
    ColorWell *red = new ColorWell(this, QColor(232, 76, 34));
    red->setFixedSize(smallColorWell);
    layout->addWidget(red, 2, 6, 1, 1);
    ColorWell *gold = new ColorWell(this, QColor(255, 192, 0));
    gold->setFixedSize(smallColorWell);
    layout->addWidget(gold, 2, 7, 1, 1);
    ColorWell *purple = new ColorWell(this, QColor(128, 100, 162));
    purple->setFixedSize(smallColorWell);
    layout->addWidget(purple, 2, 8, 1, 1);
    ColorWell *green = new ColorWell(this, QColor(112, 173, 71));
    green->setFixedSize(smallColorWell);
    layout->addWidget(green, 2, 9, 1, 1);

    // Row 3
    ColorWell *whiteA= new ColorWell(this, QColor(242, 242, 242));
    whiteA->setFixedSize(smallColorWell);
    layout->addWidget(whiteA, 3, 0, 1, 1);
    ColorWell *blackA= new ColorWell(this, QColor(127, 127, 127));
    blackA->setFixedSize(smallColorWell);
    layout->addWidget(blackA, 3, 1, 1, 1);
    ColorWell *lightGrayA = new ColorWell(this, QColor(208, 206, 206));
    lightGrayA->setFixedSize(smallColorWell);
    layout->addWidget(lightGrayA, 3, 2, 1, 1);
    ColorWell *blueGrayA = new ColorWell(this, QColor(214, 220, 228));
    blueGrayA->setFixedSize(smallColorWell);
    layout->addWidget(blueGrayA, 3, 3, 1, 1);
    ColorWell *blueA = new ColorWell(this, QColor(222, 235, 246));
    blueA->setFixedSize(smallColorWell);
    layout->addWidget(blueA, 3, 4, 1, 1);
    ColorWell *orangeA = new ColorWell(this, QColor(251, 229, 213));
    orangeA->setFixedSize(smallColorWell);
    layout->addWidget(orangeA, 3, 5, 1, 1);
    ColorWell *redA = new ColorWell(this, QColor(250, 219, 212));
    redA->setFixedSize(smallColorWell);
    layout->addWidget(redA, 3, 6, 1, 1);
    ColorWell *goldA = new ColorWell(this, QColor(255, 242, 204));
    goldA->setFixedSize(smallColorWell);
    layout->addWidget(goldA, 3, 7, 1, 1);
    ColorWell *purpleA = new ColorWell(this, QColor(229, 224, 236));
    purpleA->setFixedSize(smallColorWell);
    layout->addWidget(purpleA, 3, 8, 1, 1);
    ColorWell *greenA = new ColorWell(this, QColor(226, 239, 217));
    greenA->setFixedSize(smallColorWell);
    layout->addWidget(greenA, 3, 9, 1, 1);

    // Row 4
    ColorWell *whiteB= new ColorWell(this, QColor(216, 216, 216));
    whiteB->setFixedSize(smallColorWell);
    layout->addWidget(whiteB, 4, 0, 1, 1);
    ColorWell *blackB= new ColorWell(this, QColor(89, 89, 89));
    blackB->setFixedSize(smallColorWell);
    layout->addWidget(blackB, 4, 1, 1, 1);
    ColorWell *lightGrayB = new ColorWell(this, QColor(174, 171, 171));
    lightGrayB->setFixedSize(smallColorWell);
    layout->addWidget(lightGrayB, 4, 2, 1, 1);
    ColorWell *blueGrayB = new ColorWell(this, QColor(173, 185, 202));
    blueGrayB->setFixedSize(smallColorWell);
    layout->addWidget(blueGrayB, 4, 3, 1, 1);
    ColorWell *blueB = new ColorWell(this, QColor(189, 215, 238));
    blueB->setFixedSize(smallColorWell);
    layout->addWidget(blueB, 4, 4, 1, 1);
    ColorWell *orangeB = new ColorWell(this, QColor(247, 203, 173));
    orangeB->setFixedSize(smallColorWell);
    layout->addWidget(orangeB, 4, 5, 1, 1);
    ColorWell *redB = new ColorWell(this, QColor(245, 183, 166));
    redB->setFixedSize(smallColorWell);
    layout->addWidget(redB, 4, 6, 1, 1);
    ColorWell *goldB = new ColorWell(this, QColor(254, 229, 153));
    goldB->setFixedSize(smallColorWell);
    layout->addWidget(goldB, 4, 7, 1, 1);
    ColorWell *purpleB = new ColorWell(this, QColor(204, 193, 217));
    purpleB->setFixedSize(smallColorWell);
    layout->addWidget(purpleB, 4, 8, 1, 1);
    ColorWell *greenB = new ColorWell(this, QColor(197, 224, 179));
    greenB->setFixedSize(smallColorWell);
    layout->addWidget(greenB, 4, 9, 1, 1);

    // Row 8
    QLabel *standardLabel = new QLabel(this);
    standardLabel->setText("  Standard Colors");
    standardLabel->setMaximumHeight(30);
    layout->addWidget(standardLabel, 8, 0, 1, 10);
    standardLabel->setStyleSheet
            (
            "color: rgb(94, 94, 94);"
            "font-weight: bold;"
            "background-color: rgb(235, 235, 235);"
            );

    // Row 9
    ColorWell *stdDarkRed= new ColorWell(this, QColor(216, 216, 216));
    stdDarkRed->setFixedSize(smallColorWell);
    layout->addWidget(stdDarkRed, 9, 0, 1, 1);
    ColorWell *stdRed= new ColorWell(this, QColor(89, 89, 89));
    stdRed->setFixedSize(smallColorWell);
    layout->addWidget(stdRed, 9, 1, 1, 1);
    ColorWell *stdOrange = new ColorWell(this, QColor(174, 171, 171));
    stdOrange->setFixedSize(smallColorWell);
    layout->addWidget(stdOrange, 9, 2, 1, 1);
    ColorWell *stdYellow = new ColorWell(this, QColor(173, 185, 202));
    stdYellow->setFixedSize(smallColorWell);
    layout->addWidget(stdYellow, 9, 3, 1, 1);
    ColorWell *stdLightGreen = new ColorWell(this, QColor(189, 215, 238));
    stdLightGreen->setFixedSize(smallColorWell);
    layout->addWidget(stdLightGreen, 9, 4, 1, 1);
    ColorWell *stdGreen = new ColorWell(this, QColor(247, 203, 173));
    stdGreen->setFixedSize(smallColorWell);
    layout->addWidget(stdGreen, 9, 5, 1, 1);
    ColorWell *stdLightBlue = new ColorWell(this, QColor(245, 183, 166));
    stdLightBlue->setFixedSize(smallColorWell);
    layout->addWidget(stdLightBlue, 9, 6, 1, 1);
    ColorWell *stdBlue = new ColorWell(this, QColor(254, 229, 153));
    stdBlue->setFixedSize(smallColorWell);
    layout->addWidget(stdBlue, 9, 7, 1, 1);
    ColorWell *stdDarkBlue = new ColorWell(this, QColor(204, 193, 217));
    stdDarkBlue->setFixedSize(smallColorWell);
    layout->addWidget(stdDarkBlue, 9, 8, 1, 1);
    ColorWell *stdPurple = new ColorWell(this, QColor(197, 224, 179));
    stdPurple->setFixedSize(smallColorWell);
    layout->addWidget(stdPurple, 9, 9, 1, 1);

    // Row 10
    QPushButton *colorDialogButton = new QPushButton(this);
    colorDialogButton->setText("Other Colors");
    layout->addWidget(colorDialogButton, 10, 0, 1, 10);
    QObject::connect(colorDialogButton, SIGNAL(clicked()), this, SLOT(openColorDialog()));
}


ColorDropDownMenu::~ColorDropDownMenu()
{

}


void ColorDropDownMenu::leaveEvent(QEvent *event)
{
    this->hide();
}


void ColorDropDownMenu::openColorDialog()
{
    QColor newColor = QColorDialog::getColor
            (
                Qt::white,
                this,
                "Select Font Color",
                QColorDialog::DontUseNativeDialog
            );
}
