#include "subwindow.h"

SubWindow::SubWindow(QWidget *parent) : QMdiSubWindow(parent)
{

}

SubWindow::~SubWindow()
{
    // delete or finalize here something
}

void SubWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    this->hide();
}

