#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>

class Stack
{
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

public:
    Stack();
    virtual ~Stack();

    void write(int address);
    int read();

private:
    const int size; // Size of the Stack
    int actualPointer;
    std::vector<int> registers;

};

#endif // STACK_H
