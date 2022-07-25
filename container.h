#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include <QFrame>

class Container : public QFrame
{
    Q_OBJECT
public:
    explicit Container(QWidget *parent = nullptr);
    ~Container();

private:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:


signals:

};

#endif // CONTAINER_H
