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
#include <QFontDatabase>
#include <QTextList>
#include <QScrollArea>
#include <QSizePolicy>
#include <QScrollBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->document = new QTextDocument();
    document->setIndentWidth(10);

    this->currentContainer = nullptr;
    this->currentObject = nullptr;
    this->copiedObject = nullptr;

    // Application States
    this->bold = new bool(false);
    this->italic = new bool(false);
    this->underline = new bool(false);
    this->strike = new bool(false);

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

    // Heading 1
    QListWidgetItem *item0 = this->ui->styleListWidget->item(0);
    QFont font0;
    font0.setFamily("Sans Serif");
    font0.setPointSize(16);
    item0->setFont(font0);
    item0->setBackground(QColor::fromRgb(255, 255, 255));
    item0->setForeground(QColor::fromRgb(30, 70, 121));

    // Heading 2
    QListWidgetItem *item1 = this->ui->styleListWidget->item(1);
    QFont font1;
    font1.setFamily("Noto Sans");
    font1.setPointSize(14);
    item1->setFont(font1);
    item1->setBackground(QColor::fromRgb(255, 255, 255));
    item1->setForeground(QColor::fromRgb(46, 117, 181));

    // Heading 3
    QListWidgetItem *item2 = this->ui->styleListWidget->item(2);
    QFont font2;
    font2.setFamily("Noto Sans");
    font2.setPointSize(12);
    item2->setFont(font2);
    item2->setBackground(QColor::fromRgb(255, 255, 255));
    item2->setForeground(QColor::fromRgb(91, 155, 213));

    // Heading 4
    QListWidgetItem *item3 = this->ui->styleListWidget->item(3);
    QFont font3;
    font3.setFamily("Noto Sans");
    font3.setItalic(true);
    font3.setPointSize(12);
    item3->setFont(font3);
    item3->setBackground(QColor::fromRgb(255, 255, 255));
    item3->setForeground(QColor::fromRgb(91, 155, 213));

    //Heading 5
    QListWidgetItem *item4 = this->ui->styleListWidget->item(4);
    QFont font4;
    font4.setFamily("Noto Sans");
    font4.setPointSize(11);
    item4->setFont(font4);
    item4->setBackground(QColor::fromRgb(255, 255, 255));
    item4->setForeground(QColor::fromRgb(46, 117, 181));

    //Heading 6
    QListWidgetItem *item5 = this->ui->styleListWidget->item(5);
    QFont font5;
    font5.setFamily("Noto Sans");
    font5.setItalic(true);
    font5.setPointSize(11);
    item5->setFont(font5);
    item5->setBackground(QColor::fromRgb(255, 255, 255));
    item5->setForeground(QColor::fromRgb(46, 117, 181));

    //Page Title
    QListWidgetItem *item6 = this->ui->styleListWidget->item(6);
    QFont font6;
    font6.setFamily("Noto Sans Light");
    font6.setPointSize(20);
    item6->setFont(font6);
    item6->setBackground(QColor::fromRgb(255, 255, 255));
    item6->setForeground(QColor::fromRgb(0, 0, 0));

    // Citation
    QListWidgetItem *item7 = this->ui->styleListWidget->item(7);
    QFont font7;
    font7.setFamily("Noto Sans");
    font7.setPointSize(9);
    item7->setFont(font7);
    item7->setBackground(QColor::fromRgb(255, 255, 255));
    item7->setForeground(QColor::fromRgb(89, 89, 89));

    // Quote
    QListWidgetItem *item8 = this->ui->styleListWidget->item(8);
    QFont font8;
    font8.setFamily("Noto Sans");
    font8.setItalic(true);
    font8.setPointSize(11);
    item8->setFont(font8);
    item8->setBackground(QColor::fromRgb(255, 255, 255));
    item8->setForeground(QColor::fromRgb(89, 89, 89));

    // Code
    QListWidgetItem *item9 = this->ui->styleListWidget->item(9);
    QFont font9;
    font9.setFamily("Noto Mono");
    font9.setPointSize(11);
    item9->setFont(font9);
    item9->setBackground(QColor::fromRgb(255, 255, 255));
    item9->setForeground(QColor::fromRgb(0, 0, 0));

    // Normal
    QListWidgetItem *item10 = this->ui->styleListWidget->item(10);
    QFont font10;
    font10.setFamily("Noto Sans");
    font10.setPointSize(11);
    item10->setFont(font10);
    item10->setBackground(QColor::fromRgb(255, 255, 255));
    item10->setForeground(QColor::fromRgb(0, 0, 0));
}


MainWindow::~MainWindow()
{
    delete this->ui;
    delete this->bold;
    delete this->italic;
    delete this->underline;
    delete this->strike;
    delete this->document;
    delete this->currentFont;
    delete this->currentTextColor;
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

    QWidget *newTab = new QWidget(this);
    QVBoxLayout *tabLayout = new QVBoxLayout(newTab);
    QScrollArea *scrollArea = new QScrollArea(newTab);
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout(scrollArea);
    TabMainWidget *tabWidget = new TabMainWidget(scrollArea);

    newTab->setLayout(tabLayout);
    tabLayout->addWidget(scrollArea);
    scrollArea->setLayout(scrollAreaLayout);
    scrollAreaLayout->addWidget(tabWidget);


    tabLayout->setContentsMargins(0, 0, 0, 0);
    scrollAreaLayout->setContentsMargins(0, 0, 0, 0);

    newTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    this->ui->tabWidget->insertTab(lastTabIndex, newTab, "New Section");

    tabWidget->show();
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
    this->ui->styleListWidget->clearSelection();

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
    this->ui->styleListWidget->clearSelection();

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
    // Bullet style code to go here...
    QTextListFormat::Style style = QTextListFormat::Style::ListUpperAlpha;

    if (this->currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (textEdit)
        {    
            QTextCursor cursor = textEdit->textCursor();
            QTextListFormat listFormat;
            listFormat.setIndent(1);
            listFormat.setStyle(style);
            QTextList *list = cursor.createList(listFormat);
            list->setParent(textEdit);
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
    QListWidgetItem * normalTextItem = this->ui->styleListWidget->item(10);
    this->ui->styleListWidget->setCurrentItem(normalTextItem);
}


void MainWindow::on_copyButton_clicked()
{
//    if (this->currentContainer && this->currentObject)
//    {
//        const QTextEdit *textEdit = qobject_cast<QTextEdit*>(currentObject);
//        QClipboard *clipboard = QApplication::clipboard();

//        QMimeData richText = QMimeData();
//        richText.setHtml(textEdit->toHtml());
//        clipboard->clear();
//        clipboard->setMimeData(&richText);
//    }
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
        }    }
}


QFont MainWindow::getFormatPainterFont()
{
    return *this->formatPainterFont;
}


void MainWindow::on_styleListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    this->changeStyle(current);

}


void MainWindow::on_styleListWidget_itemClicked(QListWidgetItem *item)
{
    this->changeStyle(item);
    item->setSelected(true);
}


void MainWindow::changeStyle(QListWidgetItem *current)
{
    const QFont newFont(current->font());
    this->ui->fontComboBox->setCurrentFont(newFont);

    const int fontSize = current->font().pointSize();
    QString fontSizeText = QString::number(fontSize);
    fontSizeText.append(" pt");
    this->ui->fontSizeComboBox->setCurrentText(fontSizeText);

    if (currentObject)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(currentObject);
        if(textEdit)
        {
            textEdit->setCurrentFont(newFont);
            textEdit->setTextColor(current->foreground().color());
            textEdit->setTextBackgroundColor(current->background().color());
        }
    }

    *this->bold = current->font().bold();
    *this->italic = current->font().italic();
    *this->underline = current->font().underline();
    *this->strike = current->font().strikeOut();
    *this->currentTextColor = current->foreground().color();
}

