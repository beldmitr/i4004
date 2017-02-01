#include "iolistcomponents.h"

ioListComponents::ioListComponents(QWidget *parent) : QListWidget(parent)
{

}

ioListComponents::~ioListComponents()
{
    // delete or finalize here something
}

void ioListComponents::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event);
}

