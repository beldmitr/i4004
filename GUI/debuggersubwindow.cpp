#include "debuggersubwindow.h"

DebuggerSubWindow::DebuggerSubWindow(QWidget *parent, Compiler* compiler, Simulator *simulator) : SubWindow()
{
    this->compiler = compiler;
    this->simulator = simulator;

    debuggerLst = std::shared_ptr<DebuggerList>(new DebuggerList(compiler, simulator));

    this->setWindowTitle("Debugger");
    this->setWindowIcon(QIcon(":/Resources/icons/assembly.png"));

    this->setWidget(debuggerLst.get());

    this->move(415, 5);

    QRect r = this->geometry();
    r.setHeight(parent->height());

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
