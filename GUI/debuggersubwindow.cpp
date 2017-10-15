#include "debuggersubwindow.h"

DebuggerSubWindow::DebuggerSubWindow(Compiler* compiler) : SubWindow()
{
    this->compiler = compiler;

    debuggerLst = std::shared_ptr<DebuggerList>(new DebuggerList(compiler));

    this->setWindowTitle("Debugger");
    this->setWindowIcon(QIcon(":/Resources/icons/assembly.png"));

    this->setWidget(debuggerLst.get());
}

DebuggerSubWindow::~DebuggerSubWindow()
{

}
