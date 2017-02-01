#ifndef CPU_H
#define CPU_H

#include <QString>

#include <iostream>
#include <vector>

#include "stack.h"

/// TESTME test all cpu class how does it works
class CPU
{
private:
    int PC;
    int acc;
    int carry;
    int test;
    int cycles;
    QString operation;
    Stack* stack;
    std::vector<unsigned int> registers;
    int dcl; // chooses memory bank (0-7)

    /*
     * SRC chooses:
     * 1) DATA RAM data character
     * 2) DATA RAM status character
     * 3) RAM output port
     * 4) ROM input or output port
     */
    int src;


public:
    CPU();
    virtual ~CPU();

    int getAcc() const;
    void setAcc(unsigned int value);
    int getCarry() const;
    void setCarry(unsigned int value);
    int getTest() const;
    void setTest(unsigned int value);
    int getCycles() const;
    void setCycles(unsigned int value);
    QString getOperation() const;
    void setOperation(const QString &value);
    Stack* getStack() const;
    void setStack(const Stack &value);
    unsigned int getRegisterAt(unsigned int index) const;
    void setRegisters(unsigned int index, unsigned int value);
    unsigned int getPairAt(unsigned int index) const;
    void setPairs(unsigned int index, unsigned int value);
    int getPC() const;
    void setPC(unsigned int value);
    int getDcl() const;
    void setDcl(unsigned int value);
    int getSrc() const;
    void setSrc(unsigned int value);
};

#endif // CPU_H
