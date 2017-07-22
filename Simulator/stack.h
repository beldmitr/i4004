#ifndef STACK_H
#define STACK_H

#include <QObject>

#include <vector>
#include <iostream>

class Stack : public QObject
{
    Q_OBJECT
    /*
     * The stack consists of three 12-bit registers used to hold addresses of program instructions.
     * Since progra~s are always run in ROM or program RAM, the stack registers will always
     * refer to ROM locations or program RAM locations.
     *
     * Stack operations consist of writing an address to the stack I and reading an address
     * from the stack.
     *
     * Each stack register is adjacent to the other two stack registers. The 4004 keeps a
     * pointer to the next stack register available.
     *
     */

private:
    const int size = 4; // Size of the Stack
    int actualPointer = 0;
    std::vector<int> registers;

public:
    Stack();
    virtual ~Stack();

    void write(unsigned address);
    int read();

    int getActualPointer() const;
    std::vector<int> getRegisters() const;

    void setPC(unsigned int value);
    unsigned int getPC();

    void reset();

signals:
    void onStackChanged();

};

#endif // STACK_H
