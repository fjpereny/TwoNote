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

    void setMovable(bool);
    bool getMovable();

private:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    bool *isMovable;
    int *clickOffsetX;
    int *clickOffsetY;

private slots:


signals:

};

#endif // CONTAINER_H
