#include "debuggersubwindow.h"

DebuggerSubWindow::DebuggerSubWindow(QWidget*, Compiler* compiler, Simulator *simulator) : SubWindow()
{
    this->compiler = compiler;
    this->simulator = simulator;

    debuggerLst = std::shared_ptr<DebuggerList>(new DebuggerList(compiler, simulator));

    this->setWindowTitle("Debugger");
    this->setWindowIcon(QIcon(":/Resources/icons/assembly.png"));

    this->setWidget(debuggerLst.get());

    QDesktopWidget desktop;

    this->move(desktop.width() / 2, 5);

    QRect r = this->geometry();
    r.setHeight((desktop.height() / 2) - 100);

    QString os = QSysInfo::kernelType();
    if (os == "darwin")
    {
        r.setWidth(325);
    }
    else
    {
        r.setWidth(475);
    }

    this->setGeometry(r);

}

DebuggerSubWindow::~DebuggerSubWindow()
{

}
