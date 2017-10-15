#ifndef DEBUGGERSUBWINDOW_H
#define DEBUGGERSUBWINDOW_H

#include <QObject>
#include <QWidget>

#include "GUI/subwindow.h"
#include "GUI/debuggerlist.h"
#include "Compiler/compiler.h"

class DebuggerSubWindow : public SubWindow
{
public:
    explicit DebuggerSubWindow(Compiler *compiler);
    virtual ~DebuggerSubWindow();

private:
    std::shared_ptr<DebuggerList> debuggerLst;

    Compiler* compiler;
};

#endif // DEBUGGERSUBWINDOW_H
