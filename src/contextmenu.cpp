#include "contextmenu.h"
#include "ui_contextmenu.h"

ContextMenu::ContextMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ContextMenu)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
}

ContextMenu::~ContextMenu()
{
    delete ui;
}


void ContextMenu::focusInEvent(QFocusEvent *event)
{

}

void ContextMenu::mouseMoveEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
}
