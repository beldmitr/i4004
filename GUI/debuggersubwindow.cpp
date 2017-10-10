#include "debuggersubwindow.h"

DebuggerSubWindow::DebuggerSubWindow() : SubWindow()
{
    debuggerLst = std::shared_ptr<DebuggerList>(new DebuggerList());

    this->setWidget(debuggerLst.get());
}

DebuggerSubWindow::~DebuggerSubWindow()
{

}
