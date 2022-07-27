#include "mainwindow.h"
#include "./ui_mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentObject = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
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
    if (this->currentObject)
    {
        QTextEdit *floatTextEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (floatTextEdit)
        {
            QFont font = floatTextEdit->currentFont();
            font.setBold(!font.bold());
            floatTextEdit->setCurrentFont(font);
            return;
        }
    }
}


void MainWindow::on_italicButton_clicked()
{
    if (this->currentObject)
    {
        QTextEdit *floatTextEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (floatTextEdit)
        {
            floatTextEdit->setFontItalic(!floatTextEdit->fontItalic());
            return;
        }
    }
}


void MainWindow::on_underlineButton_clicked()
{
    if (this->currentObject)
    {
        QTextEdit *floatTextEdit = qobject_cast<QTextEdit*>(this->currentObject);
        if (floatTextEdit)
        {
            floatTextEdit->setFontUnderline(!floatTextEdit->fontUnderline());
            return;
        }
    }
}


void MainWindow::on_strikeButton_clicked()
{
    if (this->currentObject)
    {
        QTextEdit *floatTextEdit = qobject_cast<QTextEdit*>(this->currentObject);

        if (floatTextEdit)
        {
            QFont font = floatTextEdit->currentFont();
            font.setStrikeOut(!font.strikeOut());
            floatTextEdit->setCurrentFont(font);
            return;
        }
    }
}


void MainWindow::setCurrentObject(QWidget *object)
{
    this->currentObject = object;
}

QWidget* MainWindow::getCurrentObject(QWidget *object)
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
    QTextEdit *widget = qobject_cast<QTextEdit*>(this->currentObject);
    if (widget)
    {
        QString fontSizeTextPt = ui->fontSizeComboBox->currentText();
        QString fontSizeText = fontSizeTextPt.split(' ')[0];
        int fontSize = fontSizeText.toInt();

        QFont font = widget->currentFont();
        font.setPointSize(fontSize);
        widget->setCurrentFont(font);
    }
}

