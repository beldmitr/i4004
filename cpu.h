#ifndef CPU_H
#define CPU_H

#include <QString>

#include <iostream>
#include <vector>

#include "stack.h"

using namespace std;

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
    vector<int> registers;
    vector<int> pairs;
    int dcl; // chooses memory bank (0-8)

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


    int getAcc() const;
    void setAcc(int value);
    int getCarry() const;
    void setCarry(int value);
    int getTest() const;
    void setTest(int value);
    int getCycles() const;
    void setCycles(unsigned int value);
    QString getOperation() const;
    void setOperation(const QString &value);
    Stack* getStack() const;
    void setStack(const Stack &value);
    vector<int> getRegisters() const;
    void setRegisters(int index, int value);
    vector<int> getPairs() const;
    void setPairs(int index, int value);
    int getPC() const;
    void setPC(int value);
    int getDcl() const;
    void setDcl(int value);
    int getSrc() const;
    void setSrc(int value);
};

#endif // CPU_H
