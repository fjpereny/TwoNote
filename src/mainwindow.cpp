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


#include "src/mainwindow.h"
#include "src/ui_mainwindow.h"
#include "src/tabmainwidget.h"
#include "src/floattextedit.h"

#include <iostream>
#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QKeyEvent>
#include <QTextCursor>
#include <QFile>
#include <QDir>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentContainer = nullptr;
    currentObject = nullptr;

    // Application States
    bold = new bool(false);
    italic = new bool(false);
    underline = new bool(false);
    strike = new bool(false);

    this->currentFont = new QFont();
    this->currentFont->setPointSize(this->getFontSize());
    this->currentFont->setFamily(ui->fontComboBox->currentFont().family());
    this->currentFont->setBold(*bold);
    this->currentFont->setItalic(*italic);
    this->currentFont->setUnderline(*underline);
    this->currentFont->setStrikeOut(*strike);

    this->currentTextColor = new QColor(Qt::black);

    this->ui->ribbonBar->setStyleSheet
            (
                "QWidget"
                "{"
                    "margin: 0px, 0px, 0px, 0px;"
                    "padding: 0px, 0px, 0px, 0px;"
                    "color: rgb(0, 0, 0);"
                    "background-color: rgb(243, 243, 243);"
                "}"

                "QTabBar"
                "{"
                    "margin-top: 0px;"
                    "margin-bottom: 0px;"
                    "border: 0px;"
                    "background: rgb(128, 57, 123);"
                "}"

                "QTabWidget"
                "{"
                    "margin: 0px, 10px, 0px, 0px;"
                    "border: 0px;"
                "}"

                "QTabWidget::pane"
                "{"
                    "padding-bottom: 5px;"
                    "border: 0px;"
                "}"

                "QTabBar::tab:selected"
                "{"
                    "color: rgb(128, 57, 123);"
                    "background: rgb(243, 243, 243);"
                "}"

                "QTabBar::tab:!selected"
                "{"
                    "color: rgb(255, 255, 255);"
                    "background: rgb(128, 57, 123);"
                "}"

                "QTabBar::tab:!selected:hover"
                "{"
                    "color: rgb(255, 255, 255);"
                    "background: rgb(158, 84, 153);"
                "}"

                "QComboBox"
                "{"
                    "background-color: rgb(255, 255, 255);"
                "}"

                "QPushButton"
                "{"
                    "border: 0px;"
                "}"

                "QPushButton:hover"
                "{"
                    "background: rgb(198, 198, 198);"
                "}"

                "QFontComboBox"
                "{"
                    "color: black;"
                    "background-color: rgb(255, 255, 255);"
                "}"
            );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bold;
    delete italic;
    delete underline;
    delete strike;
}


Ui::MainWindow* MainWindow::getUi()
{
    return this->ui;
}


void MainWindow::on_ribbonBar_currentChanged(int index)
{

}


void MainWindow::on_tabWidget_tabBarDoubleClicked(int index)
{
    QDialog *dlg = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(dlg);
    QLineEdit *edit = new QLineEdit(dlg);
    QPushButton *ok = new QPushButton(dlg);

    edit->setText(this->ui->tabWidget->tabText(index));
    edit->setObjectName("setTabLineEdit");
    layout->addWidget(edit);

    ok->setText("Save");
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(setTabText()));
    layout->addWidget(ok);

    dlg->setWindowTitle("Rename Tab");
    dlg->setLayout(layout);
    dlg->setModal(true);
    dlg->show();

    edit->selectAll();
}


void MainWindow::setTabText()
{
    QPushButton *ok = qobject_cast<QPushButton*>(sender());
    QDialog *dlg = qobject_cast<QDialog*>(ok->parent());
    QLineEdit *edit = dlg->findChild<QLineEdit*>("setTabLineEdit");
    this->ui->tabWidget->setTabText(this->ui->tabWidget->currentIndex(), edit->text());
    dlg->close();
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    int tabCount = this->ui->tabWidget->count();
    int lastTabIndex = tabCount - 1;
    if (index != lastTabIndex)
    {
           return;
    }

    QWidget *newPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(newPage);
    newPage->setLayout(layout);
    TabMainWidget *tabWidget = new TabMainWidget(newPage);
    layout->addWidget(tabWidget);
    this->ui->tabWidget->insertTab(lastTabIndex, newPage, "New Section");
}


void MainWindow::on_boldButton_clicked()
{
    *this->bold = !(*this->bold);
    this->currentFont->setBold(*bold);

    if (this->currentContainer && this->currentContainer->hasFocus())
    {
        if (this->currentObject)
        {
            QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
            if (textEdit)
            {
                QFont font = textEdit->currentFont();
                font.setBold(this->getBold());
                textEdit->setCurrentFont(font);
            }
        }
    }
    else if (this->currentObject)
    {        
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (textEdit)
        {
            QFont font = textEdit->currentFont();
            font.setBold(*bold);
            textEdit->setCurrentFont(font);
        }
    }
}

void MainWindow::on_italicButton_clicked()
{
    *this->italic = !(*this->italic);
    this->currentFont->setItalic(*italic);

    if (this->currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (textEdit)
        {
            QFont font = textEdit->currentFont();
            font.setItalic(*italic);
            textEdit->setCurrentFont(font);
        }
    }
}

void MainWindow::on_underlineButton_clicked()
{
    *this->underline = !(*this->underline);
    this->currentFont->setUnderline(*underline);

    if (this->currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (textEdit)
        {
            QFont font = textEdit->currentFont();
            font.setUnderline(*underline);
            textEdit->setCurrentFont(font);
        }
    }
}

void MainWindow::on_strikeButton_clicked()
{
    *this->strike = !(*this->strike);
    this->currentFont->setStrikeOut(*strike);

    if (this->currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (textEdit)
        {
            QFont font = textEdit->currentFont();
            font.setStrikeOut(*strike);
            textEdit->setCurrentFont(font);
        }
    }
}

bool MainWindow::getBold()
{
    return *bold;
}

bool MainWindow::getItalic()
{
    return *italic;
}

bool MainWindow::getUnderline()
{
    return *underline;
}

bool MainWindow::getStrike()
{
    return *strike;
}


void MainWindow::setCurrentContainer(Container *container)
{
    this->currentContainer = container;
}

Container* MainWindow::getCurrentContainer()
{
    return this->currentContainer;
}

void MainWindow::setCurrentObject(QWidget *object)
{
    this->currentObject = object;
}

QWidget* MainWindow::getCurrentObject()
{
    return this->currentObject;
}


static MainWindow* getMainWindow()
{
    foreach (QWidget *widget, qApp->topLevelWidgets())
    {
        if (MainWindow *win = qobject_cast<MainWindow*>(widget))
        {
            return win;
        }
    }
    return nullptr;
}


void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    QFont font = *this->currentFont;
    font.setFamily(ui->fontComboBox->currentFont().family());
    *this->currentFont = font;

    QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
    if (textEdit)
    {
        textEdit->setCurrentFont(font);
    }
}

void MainWindow::on_fontSizeComboBox_currentIndexChanged(int index)
{
    QFont font = *this->currentFont;
    int fontSize = this->getFontSize();
    font.setPointSize(fontSize);
    *this->currentFont = font;

    QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
    if (textEdit)
    {
        textEdit->setCurrentFont(font);
    }
}

int MainWindow::getFontSize()
{
    QString fontSizeTextPt = ui->fontSizeComboBox->currentText();
    QString fontSizeText = fontSizeTextPt.split(' ')[0];
    int fontSize = fontSizeText.toInt();
    return fontSize;
}


QString MainWindow::getFontFamily()
{
    return this->ui->fontComboBox->currentFont().family();
}


QFont MainWindow::getCurrentFont()
{
    return *this->currentFont;
}


QColor MainWindow::getCurrentTextColor()
{
    return *this->currentTextColor;
}
