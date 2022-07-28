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


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabmainwidget.h"
#include "floattextedit.h"

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


    QDir dir;
    QFile file;

    QString folder = "/css/";
    QString fileName = "ribbonButtons.css";
    dir.setCurrent(QApplication::applicationDirPath() + folder);
    file.setFileName(fileName);
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            QString css = stream.readAll();
            ui->boldButton->setStyleSheet(css);
            file.close();
        }
        else
        {
            std::cout << "Warning: Failed to open CSS file - ribbonButtons.css" << std::endl;
        }
    }
    else
    {
        std::cout << "Warning: Missing CSS file - ribbonButtons.css" << std::endl;
    }
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

    if (this->currentObject)
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


void MainWindow::on_fontSizeComboBox_currentIndexChanged(int index)
{
    if (this->currentObject)
    {
        QTextEdit* textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (textEdit)
        {
            QFont font = textEdit->currentFont();
            int fontSize = this->getFontSize();
            font.setPointSize(fontSize);
            textEdit->setCurrentFont(font);
        }
    }
}


int MainWindow::getFontSize()
{
    QString fontSizeTextPt = ui->fontSizeComboBox->currentText();
    QString fontSizeText = fontSizeTextPt.split(' ')[0];
    int fontSize = fontSizeText.toInt();
    return fontSize;
}
