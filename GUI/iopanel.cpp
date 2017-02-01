#include "iopanel.h"

IOPanel::IOPanel(QWidget *parent) : QWidget(parent)
{
    // create components
    layout = new QHBoxLayout(this);
    viewArea = new ioWidget();
    lstComponents = new ioListComponents();
    splitter = new QSplitter(Qt::Horizontal);

    // add widgets to splitter
    splitter->addWidget(lstComponents);
    splitter->addWidget(viewArea);

    // splitter settings
    splitter->setCollapsible(0, false);
    splitter->setCollapsible(1, false);

    // Size Policy
    QSizePolicy sp;
    sp = viewArea->sizePolicy();
    sp.setHorizontalStretch(10);
    viewArea->setSizePolicy(sp);

    sp = lstComponents->sizePolicy();
    sp.setHorizontalStretch(2);
    lstComponents->setSizePolicy(sp);

    // setting ScrollArea
//    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // add elements to list
    new QListWidgetItem(QIcon(":/Resources/components/push_button.png"), "Push button", lstComponents);
    new QListWidgetItem(QIcon(":/Resources/components/button.png"), "Button", lstComponents);
    new QListWidgetItem(QIcon(":/Resources/components/7segment.png"), "7 segment", lstComponents);
    new QListWidgetItem(QIcon(":/Resources/components/led.png"), "LED", lstComponents);

    // list settings
    lstComponents->setDragEnabled(true);

    // add to layout
    layout->addWidget(splitter);
}

IOPanel::~IOPanel()
{
    // delete or finalize here something
}

ioWidget* IOPanel::getIOWidget()
{
    return viewArea;
}
