#include "subwindow.h"

SubWindow::SubWindow(QWidget *parent) : QMdiSubWindow(parent)
{

}

void SubWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    this->hide();
}



