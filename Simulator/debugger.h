#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QObject>

#include <memory>
#include <unordered_set>

class Debugger : public QObject
{
    Q_OBJECT
public:
    explicit Debugger(QObject *parent = nullptr);

    static bool hasNextByte(unsigned code);
    static QString codeToInstruction(unsigned code);
    static QString commandToString(unsigned code);
    static QString addressToString(unsigned addr);
    static QString lengthCommand(unsigned code);

    static void addBreakpoint(unsigned addr);
    static void removeBreakpoint(unsigned addr);
    static void clearBreakpoint();

    static bool isBreakpoint(unsigned addr);

private:
    static std::unordered_set<unsigned> breakpointAddresses;

};

#endif // DEBUGGER_H
