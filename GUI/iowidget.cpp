#include "iowidget.h"

ioWidget::ioWidget(QWidget *parent) : QScrollArea(parent)
{
    setAcceptDrops(true);
    //    std::cout << parent->objectName().toStdString() << "\n";
}

ioWidget::~ioWidget()
{
    // delete or finalize here something
}

void ioWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
    std::cout << "dragEnterEvent" << std::endl;
}

void ioWidget::dragLeaveEvent(QDragLeaveEvent */*event*/)
{
    std::cout << "dragLeaveEvent" << std::endl;
}

void ioWidget::dragMoveEvent(QDragMoveEvent */*event*/)
{
//    std::cout << "dragMoveEvent" << std::endl;
}

void ioWidget::dropEvent(QDropEvent */*event*/)
{
    std::cout << "dropEvent" << std::endl;
}
