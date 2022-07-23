#ifndef NOTETABWIDGET_H
#define NOTETABWIDGET_H

#include <QTabWidget>

class NoteTabWidget : public QTabWidget
{
public:
    NoteTabWidget(QWidget *parent = nullptr);
    ~NoteTabWidget();

private:
    void mousePressEvent(QMouseEvent *event);

private slots:

};

#endif // NOTETABWIDGET_H
