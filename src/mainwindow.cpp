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
#include "floatimage.h"

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
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QAbstractTextDocumentLayout>
#include <QClipboard>
#include <QMimeData>
#include <QTextCursor>
#include <QTextDocument>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->document = new QTextDocument();
    document->setIndentWidth(10);

    currentContainer = nullptr;
    currentObject = nullptr;
    copiedObject = nullptr;

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

    this->formatPainterFont = nullptr;

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


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
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
    this->currentFont->setBold(*this->bold);

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
    this->currentFont->setItalic(*this->italic);

    if (this->currentContainer && this->currentContainer->hasFocus())
    {
        if (this->currentObject)
        {
            QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
            if (textEdit)
            {
                QFont font = textEdit->currentFont();
                font.setItalic(*this->italic);
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
            font.setItalic(*this->italic);
            textEdit->setCurrentFont(font);
        }
    }
}

void MainWindow::on_underlineButton_clicked()
{
    *this->underline = !(*this->underline);
    this->currentFont->setUnderline(*this->underline);

    if (this->currentContainer && this->currentContainer->hasFocus())
    {
        if (this->currentObject)
        {
            QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
            if (textEdit)
            {
                QFont font = textEdit->currentFont();
                font.setUnderline(*this->underline);
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
            font.setUnderline(*this->underline);
            textEdit->setCurrentFont(font);
        }
    }
}

void MainWindow::on_strikeButton_clicked()
{
    *this->strike = !(*this->strike);
    this->currentFont->setStrikeOut(*this->strike);

    if (this->currentContainer && this->currentContainer->hasFocus())
    {
        if (this->currentObject)
        {
            QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
            if (textEdit)
            {
                QFont font = textEdit->currentFont();
                font.setStrikeOut(*this->strike);
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
            font.setStrikeOut(*this->strike);
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
    if (this->currentContainer)
    {
        return this->currentContainer;
    }
    else
    {
        return nullptr;
    }
}

void MainWindow::setCurrentObject(QWidget *object)
{
    this->currentObject = object;
}

QWidget* MainWindow::getCurrentObject()
{
    if (this->currentObject)
    {
        return this->currentObject;
    }
    else
    {
        return nullptr;
    }
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


void MainWindow::setCurrentFont(QFont font)
{
    *this->currentFont = font;
}


QFont MainWindow::getCurrentFont()
{
    return *this->currentFont;
}


QColor MainWindow::getCurrentTextColor()
{
    return *this->currentTextColor;
}

void MainWindow::on_bulletsButton_clicked()
{
    if (this->currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (textEdit)
        {
            QTextListFormat::Style style = QTextListFormat::ListCircle;
            QTextCursor cursor = textEdit->textCursor();
            QTextListFormat listFormat;
            listFormat.setStyle(style);
            cursor.createList(listFormat);
        }
    }
}


void MainWindow::on_numberingButton_clicked()
{
    if (this->currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (textEdit)
        {
            QTextListFormat::Style style = QTextListFormat::ListDecimal;
            QTextCursor cursor = textEdit->textCursor();
            QTextListFormat listFormat;
            listFormat.setStyle(style);
            cursor.createList(listFormat);
        }
    }
}


void MainWindow::on_exitButton_clicked()
{
    this->close();
}


void MainWindow::on_printButton_clicked()
{
    QPdfWriter pdfWriter("test.pdf");
    QPageSize pageSize(QPageSize::A4);
    pdfWriter.setPageSize(pageSize);
    pdfWriter.newPage();
    pdfWriter.setTitle("Title of Test Document");
    QPainter painter(&pdfWriter);

    TabMainWidget *tabMainWidget = ui->tabWidget->findChild<TabMainWidget*>();
    if (tabMainWidget)
    {
        QObjectList children = tabMainWidget->children();
        for (int i = 0; i < children.count(); ++i)
        {
            Container *container = qobject_cast<Container*>(children[i]);
            if (container)
            {
                FloatTextEdit *textEdit = container->findChild<FloatTextEdit*>();
                if (textEdit)
                {
                    painter.resetTransform();
                    painter.scale(10, 10);
                    painter.translate(container->pos());

                    QTextDocument td;
                    td.setHtml(textEdit->toHtml());
                    td.setDocumentMargin(0);
                    int pagePixWidth = QApplication::primaryScreen()->geometry().width() / 2;
                    int pagePixHeight = 0;
                    if (pageSize == QPageSize::Letter)
                    {
                           pagePixHeight = pagePixWidth * 11 / 8.5;
                    }
                    else if (pageSize == QPageSize::A4)
                    {
                        pagePixHeight = pagePixWidth * 297 / 210;
                    }
                    td.setPageSize(QSize(pagePixWidth, pagePixHeight));
                    td.drawContents(&painter);
                }

                FloatImage *floatImage = container->findChild<FloatImage*>();
                if (floatImage)
                {
                    QImage img = floatImage->getImage();
                    img = img.scaled(floatImage->size());
                    painter.resetTransform();
                    painter.scale(10, 10);
                    painter.translate(container->pos());
                    painter.drawImage(floatImage->pos(), img);
                }
            }
        }
    }
    QUrl url("test.pdf");
    QDesktopServices::openUrl(url);
}


void MainWindow::on_deleteButton_clicked()
{
    if (this->currentContainer)
    {
        this->currentContainer->close();
    }
    else if (this->currentObject)
    {
        this->currentObject->close();
    }
}


void MainWindow::on_clearFormatButton_clicked()
{

}


void MainWindow::on_copyButton_clicked()
{
    if (this->currentContainer && this->currentObject)
    {
        const QTextEdit *textEdit = qobject_cast<QTextEdit*>(currentObject);
        QClipboard *clipboard = QApplication::clipboard();

//        QMimeData richText = QMimeData();
//        richText.setHtml(textEdit->toHtml());
//        clipboard->clear();
//        clipboard->setMimeData(&richText);
    }
}


void MainWindow::on_indentButton_clicked()
{
    if (this->currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        QTextCursor cursor = textEdit->textCursor();
        QTextBlockFormat format = cursor.blockFormat();
        format.setTextIndent(format.indent() + 1);
        cursor.setBlockFormat(format);
        textEdit->setTextCursor(cursor);
    }
}


void MainWindow::on_outdentButton_clicked()
{
    if (this->currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        QTextCursor cursor = textEdit->textCursor();
        QTextBlockFormat format = cursor.blockFormat();
        if (format.indent() >= 0)
        {
            format.setTextIndent(format.indent() - 1);
            cursor.setBlockFormat(format);
            textEdit->setTextCursor(cursor);
        }
    }
}


void MainWindow::on_formatPainterButton_clicked()
{
    if (currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(currentObject);
        if(textEdit)
        {
            if (formatPainterFont)
            {
                delete formatPainterFont;
            }
            formatPainterFont = new QFont(textEdit->currentFont());
        }

    }
}


QFont MainWindow::getFormatPainterFont()
{
    return *this->formatPainterFont;
}
