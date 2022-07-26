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
    this->mainWindow = qobject_cast<MainWindow*>(parent);

    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
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
                "border-color : rgb(191, 191, 191);"
                "}"
            );

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(2, 2, 2, 2);
    this->setLayout(layout);

    QSize largeColorWell(20, 20);
    QSize smallColorWell(15, 15);

    // Row 0
    layout->setRowStretch(0, 1);
    ColorWell *automatic = new ColorWell(this, Qt::black);
    automatic->setFixedSize(largeColorWell);
    layout->addWidget(automatic, 0, 0, 1, 2);

    QLabel *automaticText = new QLabel(this);
    automaticText->setText("Automatic");
    automaticText->setFixedHeight(28);
    layout->addWidget(automaticText, 0, 2, 1, 8);
    automaticText->setStyleSheet
            (
                "color: black;"
            );

    // Row 1
    layout->setRowStretch(1, 1);
    QLabel *themeColorsLabel = new QLabel(this);
    themeColorsLabel->setText("  Theme Colors");
    themeColorsLabel->setFixedHeight(30);
    layout->addWidget(themeColorsLabel, 1, 0, 1, 10);
    themeColorsLabel->setStyleSheet
            (
            "color: rgb(94, 94, 94);"
            "font-weight: bold;"
            "background-color: rgb(235, 235, 235);"
            );

    // Row 2
    layout->setRowStretch(2, 1);
    ColorWell *white= new ColorWell(this, Qt::white);
    white->setFixedSize(smallColorWell);
    white->setToolTip("<h4 style=\"color: black;\">White</h4>");
    layout->addWidget(white, 2, 0, 1, 1);
    ColorWell *black= new ColorWell(this, Qt::black);
    black->setFixedSize(smallColorWell);
    black->setToolTip("<h4>Black</h4>");
    layout->addWidget(black, 2, 1, 1, 1);
    ColorWell *lightGray = new ColorWell(this, QColor(231, 230, 230));
    lightGray->setFixedSize(smallColorWell);
    lightGray->setToolTip("<h4 style=\"color: black;\">Light Gray</h4>");
    layout->addWidget(lightGray, 2, 2, 1, 1);
    ColorWell *blueGray = new ColorWell(this, QColor(68, 84, 106));
    blueGray->setFixedSize(smallColorWell);
    blueGray->setToolTip("<h4>Blue-Gray</h4>");
    layout->addWidget(blueGray, 2, 3, 1, 1);
    ColorWell *blue = new ColorWell(this, QColor(91, 155, 213));
    blue->setFixedSize(smallColorWell);
    blue->setToolTip("<h4>Blue</h4>");
    layout->addWidget(blue, 2, 4, 1, 1);
    ColorWell *orange = new ColorWell(this, QColor(237, 125, 49));
    orange->setFixedSize(smallColorWell);
    orange->setToolTip("<h4>Orange</h4>");
    layout->addWidget(orange, 2, 5, 1, 1);
    ColorWell *red = new ColorWell(this, QColor(232, 76, 34));
    red->setFixedSize(smallColorWell);
    red->setToolTip("<h4>Red</h4>");
    layout->addWidget(red, 2, 6, 1, 1);
    ColorWell *gold = new ColorWell(this, QColor(255, 192, 0));
    gold->setFixedSize(smallColorWell);
    gold->setToolTip("<h4 style=\"color: black;\">Gold</h4>");
    layout->addWidget(gold, 2, 7, 1, 1);
    ColorWell *purple = new ColorWell(this, QColor(128, 100, 162));
    purple->setFixedSize(smallColorWell);
    purple->setToolTip("<h4>Purple</h4>");
    layout->addWidget(purple, 2, 8, 1, 1);
    ColorWell *green = new ColorWell(this, QColor(112, 173, 71));
    green->setFixedSize(smallColorWell);
    green->setToolTip("<h4>Green</h4>");
    layout->addWidget(green, 2, 9, 1, 1);

    // Row 3
    layout->setRowStretch(3, 2);
    ColorWell *whiteA= new ColorWell(this, QColor(242, 242, 242));
    whiteA->setFixedSize(smallColorWell);
    whiteA->setToolTip("<h4 style=\"color: black;\">White, Darker 5%</h4>");
    layout->addWidget(whiteA, 3, 0, 1, 1);
    ColorWell *blackA= new ColorWell(this, QColor(127, 127, 127));
    blackA->setFixedSize(smallColorWell);
    blackA->setToolTip("<h4>Black, Lighter 50%</h4>");
    layout->addWidget(blackA, 3, 1, 1, 1);
    ColorWell *lightGrayA = new ColorWell(this, QColor(208, 206, 206));
    lightGrayA->setFixedSize(smallColorWell);
    lightGrayA->setToolTip("<h4 style=\"color: black;\">Light Gray, Darker 10%</h4>");
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
    layout->setRowStretch(4, 2);
    ColorWell *whiteB= new ColorWell(this, QColor(216, 216, 216));
    whiteB->setFixedSize(smallColorWell);
    whiteB->setToolTip("<h4 style=\"color: black;\">White, Darker 15%</h4>");
    layout->addWidget(whiteB, 4, 0, 1, 1);
    ColorWell *blackB= new ColorWell(this, QColor(89, 89, 89));
    blackB->setFixedSize(smallColorWell);
    blackB->setToolTip("<h4>Black, Lighter 35%</h4>");
    layout->addWidget(blackB, 4, 1, 1, 1);
    ColorWell *lightGrayB = new ColorWell(this, QColor(174, 171, 171));
    lightGrayB->setFixedSize(smallColorWell);
    lightGrayB->setToolTip("<h4 style=\"color: black;\">Light Gray, Darker 25%</h4>");
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

    // Row 5
    layout->setRowStretch(5, 2);
    ColorWell *whiteC= new ColorWell(this, QColor(191, 191, 191));
    whiteC->setFixedSize(smallColorWell);
    whiteC->setToolTip("<h4 style=\"color: black;\">White, Darker 25%</h4>");
    layout->addWidget(whiteC, 5, 0, 1, 1);
    ColorWell *blackC= new ColorWell(this, QColor(63, 63, 63));
    blackC->setFixedSize(smallColorWell);
    blackC->setToolTip("<h4>Black, Lighter 25%</h4>");
    layout->addWidget(blackC, 5, 1, 1, 1);
    ColorWell *lightGrayC = new ColorWell(this, QColor(117, 112, 112));
    lightGrayC->setFixedSize(smallColorWell);
    lightGrayC->setToolTip("<h4>Light Gray, Darker 50%</h4>");
    layout->addWidget(lightGrayC, 5, 2, 1, 1);
    ColorWell *blueGrayC = new ColorWell(this, QColor(132, 150, 176));
    blueGrayC->setFixedSize(smallColorWell);
    layout->addWidget(blueGrayC, 5, 3, 1, 1);
    ColorWell *blueC = new ColorWell(this, QColor(156, 195, 229));
    blueC->setFixedSize(smallColorWell);
    layout->addWidget(blueC, 5, 4, 1, 1);
    ColorWell *orangeC = new ColorWell(this, QColor(244, 177, 131));
    orangeC->setFixedSize(smallColorWell);
    layout->addWidget(orangeC, 5, 5, 1, 1);
    ColorWell *redC = new ColorWell(this, QColor(241, 147, 122));
    redC->setFixedSize(smallColorWell);
    layout->addWidget(redC, 5, 6, 1, 1);
    ColorWell *goldC = new ColorWell(this, QColor(255, 217, 101));
    goldC->setFixedSize(smallColorWell);
    layout->addWidget(goldC, 5, 7, 1, 1);
    ColorWell *purpleC = new ColorWell(this, QColor(178, 161, 199));
    purpleC->setFixedSize(smallColorWell);
    layout->addWidget(purpleC, 5, 8, 1, 1);
    ColorWell *greenC = new ColorWell(this, QColor(168, 208, 141));
    greenC->setFixedSize(smallColorWell);
    layout->addWidget(greenC, 5, 9, 1, 1);

    // Row 6
    layout->setRowStretch(6, 2);
    ColorWell *whiteD= new ColorWell(this, QColor(165, 165, 165));
    whiteD->setFixedSize(smallColorWell);
    whiteD->setToolTip("<h4 style=\"color: black;\">White, Darker 35%</h4>");
    layout->addWidget(whiteD, 6, 0, 1, 1);
    ColorWell *blackD= new ColorWell(this, QColor(38, 38, 38));
    blackD->setFixedSize(smallColorWell);
    blackD->setToolTip("<h4>Black, Lighter 15%</h4>");
    layout->addWidget(blackD, 6, 1, 1, 1);
    ColorWell *lightGrayD = new ColorWell(this, QColor(58, 56, 56));
    lightGrayD->setFixedSize(smallColorWell);
    lightGrayD->setToolTip("<h4>Light Gray, Darker 75%</h4>");
    layout->addWidget(lightGrayD, 6, 2, 1, 1);
    ColorWell *blueGrayD = new ColorWell(this, QColor(50, 63, 79));
    blueGrayD->setFixedSize(smallColorWell);
    layout->addWidget(blueGrayD, 6, 3, 1, 1);
    ColorWell *blueD = new ColorWell(this, QColor(46, 117, 181));
    blueD->setFixedSize(smallColorWell);
    layout->addWidget(blueD, 6, 4, 1, 1);
    ColorWell *orangeD = new ColorWell(this, QColor(197, 90, 17));
    orangeD->setFixedSize(smallColorWell);
    layout->addWidget(orangeD, 6, 5, 1, 1);
    ColorWell *redD = new ColorWell(this, QColor(180, 53, 18));
    redD->setFixedSize(smallColorWell);
    layout->addWidget(redD, 6, 6, 1, 1);
    ColorWell *goldD = new ColorWell(this, QColor(191, 144, 0));
    goldD->setFixedSize(smallColorWell);
    layout->addWidget(goldD, 6, 7, 1, 1);
    ColorWell *purpleD = new ColorWell(this, QColor(95, 73, 122));
    purpleD->setFixedSize(smallColorWell);
    layout->addWidget(purpleD, 6, 8, 1, 1);
    ColorWell *greenD = new ColorWell(this, QColor(83, 129, 53));
    greenD->setFixedSize(smallColorWell);
    layout->addWidget(greenD, 6, 9, 1, 1);

    // Row 7
    layout->setRowStretch(7, 2);
    ColorWell *whiteE= new ColorWell(this, QColor(127, 127, 127));
    whiteE->setFixedSize(smallColorWell);
    whiteE->setToolTip("<h4>White, Darker 50%</h4>");
    layout->addWidget(whiteE, 7, 0, 1, 1);
    ColorWell *blackE= new ColorWell(this, QColor(12, 12, 12));
    blackE->setFixedSize(smallColorWell);
    blackE->setToolTip("<h4>Black, Lighter 5%</h4>");
    layout->addWidget(blackE, 7, 1, 1, 1);
    ColorWell *lightGrayE = new ColorWell(this, QColor(23, 22, 22));
    lightGrayE->setFixedSize(smallColorWell);
    lightGrayE->setToolTip("<h4>Light Gray, Darker 90%</h4>");
    layout->addWidget(lightGrayE, 7, 2, 1, 1);
    ColorWell *blueGrayE = new ColorWell(this, QColor(34, 42, 53));
    blueGrayE->setFixedSize(smallColorWell);
    layout->addWidget(blueGrayE, 7, 3, 1, 1);
    ColorWell *blueE = new ColorWell(this, QColor(30, 78, 121));
    blueE->setFixedSize(smallColorWell);
    layout->addWidget(blueE, 7, 4, 1, 1);
    ColorWell *orangeE = new ColorWell(this, QColor(131, 60, 11));
    orangeE->setFixedSize(smallColorWell);
    layout->addWidget(orangeE, 7, 5, 1, 1);
    ColorWell *redE = new ColorWell(this, QColor(120, 35, 12));
    redE->setFixedSize(smallColorWell);
    layout->addWidget(redE, 7, 6, 1, 1);
    ColorWell *goldE = new ColorWell(this, QColor(127, 96, 0));
    goldE->setFixedSize(smallColorWell);
    layout->addWidget(goldE, 7, 7, 1, 1);
    ColorWell *purpleE = new ColorWell(this, QColor(63, 49, 81));
    purpleE->setFixedSize(smallColorWell);
    layout->addWidget(purpleE, 7, 8, 1, 1);
    ColorWell *greenE = new ColorWell(this, QColor(55, 86, 35));
    greenE->setFixedSize(smallColorWell);
    layout->addWidget(greenE, 7, 9, 1, 1);

    // Row 8
    layout->setRowStretch(8, 1);
    QLabel *standardLabel = new QLabel(this);
    standardLabel->setText("  Standard Colors");
    standardLabel->setFixedHeight(30);
    layout->addWidget(standardLabel, 8, 0, 1, 10);
    standardLabel->setStyleSheet
            (
            "color: rgb(94, 94, 94);"
            "font-weight: bold;"
            "background-color: rgb(235, 235, 235);"
            );

    // Row 9
    layout->setRowStretch(9, 1);
    ColorWell *stdDarkRed= new ColorWell(this, QColor(192, 0, 0));
    stdDarkRed->setFixedSize(smallColorWell);
    stdDarkRed->setToolTip("<h4>Dark Red</h4>");
    layout->addWidget(stdDarkRed, 9, 0, 1, 1);
    ColorWell *stdRed= new ColorWell(this, QColor(255, 0, 0));
    stdRed->setFixedSize(smallColorWell);
    stdRed->setToolTip("<h4>Red</h4>");
    layout->addWidget(stdRed, 9, 1, 1, 1);
    ColorWell *stdOrange = new ColorWell(this, QColor(255, 192, 0));
    stdOrange->setFixedSize(smallColorWell);
    stdOrange->setToolTip("<h4 style=\"color: black;\">Orange</h4>");
    layout->addWidget(stdOrange, 9, 2, 1, 1);
    ColorWell *stdYellow = new ColorWell(this, QColor(255, 255, 0));
    stdYellow->setFixedSize(smallColorWell);
    stdYellow->setToolTip("<h4 style=\"color: black;\">Yellow</h4>");
    layout->addWidget(stdYellow, 9, 3, 1, 1);
    ColorWell *stdLightGreen = new ColorWell(this, QColor(146, 208, 80));
    stdLightGreen->setFixedSize(smallColorWell);
    stdLightGreen->setToolTip("<h4 style=\"color: black;\">Light Green</h4>");
    layout->addWidget(stdLightGreen, 9, 4, 1, 1);
    ColorWell *stdGreen = new ColorWell(this, QColor(0, 176, 80));
    stdGreen->setFixedSize(smallColorWell);
    stdGreen->setToolTip("<h4>Green</h4>");
    layout->addWidget(stdGreen, 9, 5, 1, 1);
    ColorWell *stdLightBlue = new ColorWell(this, QColor(0, 176, 240));
    stdLightBlue->setFixedSize(smallColorWell);
    stdLightBlue->setToolTip("<h4 style=\"color: black;\">Light Blue</h4>");
    layout->addWidget(stdLightBlue, 9, 6, 1, 1);
    ColorWell *stdBlue = new ColorWell(this, QColor(0, 112, 192));
    stdBlue->setFixedSize(smallColorWell);
    stdBlue->setToolTip("<h4>Blue</h4>");
    layout->addWidget(stdBlue, 9, 7, 1, 1);
    ColorWell *stdDarkBlue = new ColorWell(this, QColor(0, 32, 96));
    stdDarkBlue->setFixedSize(smallColorWell);
    stdDarkBlue->setToolTip("<h4>Dark Blue</h4>");
    layout->addWidget(stdDarkBlue, 9, 8, 1, 1);
    ColorWell *stdPurple = new ColorWell(this, QColor(112, 48, 160));
    stdPurple->setFixedSize(smallColorWell);
    stdPurple->setToolTip("<h4>Purple</h4>");
    layout->addWidget(stdPurple, 9, 9, 1, 1);

    // Row 10
    layout->setRowStretch(10, 1);
    QPushButton *colorDialogButton = new QPushButton(this);
    QIcon colorDialogIcon(":/icons/fontawesome/solid/fontawesome-free-6.1.2-desktop/svgs/solid/palette.svg");
    colorDialogButton->setIcon(colorDialogIcon);
    colorDialogButton->setText("\tMore Colors...");
    colorDialogButton->setFlat(true);
    colorDialogButton->setFixedHeight(30);
    colorDialogButton->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(colorDialogButton, 10, 0, 1, 10);
    QObject::connect(colorDialogButton, SIGNAL(clicked()), this, SLOT(openColorDialog()));
    colorDialogButton->setStyleSheet
            (
                "QPushButton"
                "{"
                    "text-align: left;"
                    "color: black;"
                    "border-width: 0px;"
                    "border-color: white;"
                    "border-radius: 0px;"
                    "background-color: white;"
                "}"

                "QPushButton::Hover"
                "{"
                    "color: black;"
                    "border-width: 0px;"
                    "border-color: white;"
                    "border-radius: 0px;"
                    "background-color: rgb(197, 197, 197);"
                "}"

            );

    this->adjustSize();
}


ColorDropDownMenu::~ColorDropDownMenu()
{

}


void ColorDropDownMenu::leaveEvent(QEvent *event)
{

}


void ColorDropDownMenu::openColorDialog()
{
    this->hide();

    QColor color = this->mainWindow->getTextDialogColor();
    if (color == Qt::black)
    {
        color = Qt::white;
    }
    color = QColorDialog::getColor
            (
                color,
                this,
                "Select Font Color",
                QColorDialog::DontUseNativeDialog
            );
    this->mainWindow->setTextDialogColor(color);
    this->mainWindow->setCurrentTextColor(color);

    QWidget *currentObject = this->mainWindow->getCurrentObject();
    if (currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(currentObject);
        if(textEdit)
        {
            textEdit->setTextColor(color);
        }
    }
}
