#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ribbonBar_currentChanged(int index);
    void on_tabWidget_tabBarDoubleClicked(int index);
    void setTabText();
    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
