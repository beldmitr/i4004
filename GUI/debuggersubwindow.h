#ifndef DEBUGGERSUBWINDOW_H
#define DEBUGGERSUBWINDOW_H

#include <QObject>
#include <QWidget>

#include "GUI/subwindow.h"
#include "GUI/debuggerlist.h"
#include "Compiler/compiler.h"
#include "Simulator/simulator.h"

class DebuggerSubWindow : public SubWindow
{
public:
    explicit DebuggerSubWindow(QWidget *parent, Compiler *compiler, Simulator* simulator);
    virtual ~DebuggerSubWindow();

private:
    std::shared_ptr<DebuggerList> debuggerLst;

    Compiler* compiler;
    Simulator* simulator;
};

#endif // DEBUGGERSUBWINDOW_H
