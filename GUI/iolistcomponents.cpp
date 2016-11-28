#include "iolistcomponents.h"

ioListComponents::ioListComponents(QWidget *parent) : QListWidget(parent)
{

}

void ioListComponents::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event);
}

