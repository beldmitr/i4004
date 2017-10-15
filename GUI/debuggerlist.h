#ifndef DEBUGGERLIST_H
#define DEBUGGERLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>

#include <memory>
#include <vector>

#include "Simulator/debugger.h"
#include "Compiler/compiler.h"

class DebuggerList : public QTableWidget
{
    Q_OBJECT
public:
    explicit DebuggerList(Compiler *compiler = nullptr);
    virtual ~DebuggerList();

private:
    const unsigned columnNumbers = 2;

    std::vector<QTableWidgetItem*> items;
    Compiler* compiler;

    void setCode(std::vector<unsigned> code);

signals:

public slots:
};

#endif // DEBUGGERLIST_H
