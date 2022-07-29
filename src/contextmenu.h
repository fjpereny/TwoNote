#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include <QFrame>

namespace Ui {
class ContextMenu;
}

class ContextMenu : public QFrame
{
    Q_OBJECT

public:
    explicit ContextMenu(QWidget *parent = nullptr);
    ~ContextMenu();

signals:

private slots:
    void focusInEvent(QFocusEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::ContextMenu *ui;
};

#endif // CONTEXTMENU_H
