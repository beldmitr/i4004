#ifndef DEBUGGERSUBWINDOW_H
#define DEBUGGERSUBWINDOW_H

#include <QObject>
#include <QWidget>

#include "GUI/subwindow.h"
#include "GUI/debuggerlist.h"

class DebuggerSubWindow : public SubWindow
{
public:
    explicit DebuggerSubWindow();
    virtual ~DebuggerSubWindow();

private:
    std::shared_ptr<DebuggerList> debuggerLst;
};

#endif // DEBUGGERSUBWINDOW_H
