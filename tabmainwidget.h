#ifndef TABMAINWIDGET_H
#define TABMAINWIDGET_H

#include <QWidget>
#include "notetabwidget.h"

class TabMainWidget : public QWidget
{
    Q_OBJECT
public:
    TabMainWidget(QWidget *parent = nullptr);
    ~TabMainWidget();

    int *clicked_x;
    int *clicked_y;

private:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private slots:

signals:

};

#endif // TABMAINWIDGET_H
