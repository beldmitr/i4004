#include "debuggersubwindow.h"

DebuggerSubWindow::DebuggerSubWindow(Compiler* compiler, Simulator *simulator) : SubWindow()
{
    this->compiler = compiler;
    this->simulator = simulator;

    debuggerLst = std::shared_ptr<DebuggerList>(new DebuggerList(compiler, simulator));

    this->setWindowTitle("Debugger");
    this->setWindowIcon(QIcon(":/Resources/icons/assembly.png"));

    this->setWidget(debuggerLst.get());
}

DebuggerSubWindow::~DebuggerSubWindow()
{

}
