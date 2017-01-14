#include "cpuwidget.h"

CpuWidget::CpuWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    this->setLayout(layout);

    stackLayout = new QGridLayout();
    registersLayout = new QGridLayout();
    otherLayout = new QVBoxLayout();

    stackWidget = new StackWidget();

    layout->addWidget(stackWidget, 0, 0);
    layout->addLayout(registersLayout, 0, 1);
    layout->addLayout(otherLayout, 1, 0, 1, 2);


}

CpuWidget::~CpuWidget()
{
    delete(layout);

    delete(stackLayout);
    delete(registersLayout);
    delete(otherLayout);

    delete(stackWidget);
}
