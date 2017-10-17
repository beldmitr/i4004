#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QObject>

class Debugger : public QObject
{
    Q_OBJECT
public:
    explicit Debugger(QObject *parent = nullptr);

    static bool hasNextByte(unsigned code);
    static QString codeToInstruction(unsigned code);
    static QString commandToString(unsigned code);
    static QString addressToString(unsigned addr);

signals:

public slots:
};

#endif // DEBUGGER_H
