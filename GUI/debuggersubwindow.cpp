#include "debuggersubwindow.h"

DebuggerSubWindow::DebuggerSubWindow(Compiler* compiler, Simulator *simulator) : SubWindow()
{
    this->compiler = compiler;
    this->simulator = simulator;

    debuggerLst = std::shared_ptr<DebuggerList>(new DebuggerList(compiler, simulator));

    this->setWindowTitle("Debugger");
    this->setWindowIcon(QIcon(":/Resources/icons/assembly.png"));

    this->setWidget(debuggerLst.get());

    this->move(415, 5);
//    this->move(15, 15);

    QRect r = this->geometry();
    r.setHeight(525);

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
