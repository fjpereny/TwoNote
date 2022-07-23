#ifndef RIBBONBAR_H
#define RIBBONBAR_H

#include <QTabWidget>

class RibbonBar : public QTabWidget
{
public:
    RibbonBar(QWidget *parent = nullptr);
    ~RibbonBar();
};

#endif // RIBBONBAR_H
