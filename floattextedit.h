#ifndef FLOATTEXTEDIT_H
#define FLOATTEXTEDIT_H

#include <QTextEdit>

class FloatTextEdit : public QTextEdit
{
public:
    FloatTextEdit(QWidget *parent = nullptr);
    ~FloatTextEdit();

    bool *selected;

private:
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void fontSizeUp();
    void fontSizeDown();

signals:


private slots:
    void changeParentCursor();
};

#endif // FLOATTEXTEDIT_H
