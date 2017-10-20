#ifndef DEBUGGERLIST_H
#define DEBUGGERLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QPainter>
#include <QDesktopWidget>

#include <memory>
#include <unordered_map>

#include "Simulator/debugger.h"
#include "Compiler/compiler.h"
#include "Simulator/simulator.h"

class DebuggerList : public QTableWidget
{
    Q_OBJECT
public:
    explicit DebuggerList(Compiler *compiler, Simulator* simulator);
    virtual ~DebuggerList();

    void selectAddress(unsigned addr);
    void deselectAll();

private:
    const unsigned columnNumbers = 4;
    const unsigned rowNumbers = 0x1000; // [0x0 - 0xFFF]

    std::unordered_map<unsigned, unsigned> addrToRow;
    Compiler* compiler;
    Simulator* simulator;

    void setCode(std::vector<unsigned> code);
    void init();

signals:

public slots:

};

#endif // DEBUGGERLIST_H
