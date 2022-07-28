#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "container.h"

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

    static MainWindow* getMainWindow();
    Ui::MainWindow* getUi();

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

private:
    Ui::MainWindow *ui;
    QWidget *currentObject;
    Container *currentContainer;

    // Application States
    bool *bold;
    bool *italic;
    bool *underscore;
    bool *strike;
};
#endif // MAINWINDOW_H
