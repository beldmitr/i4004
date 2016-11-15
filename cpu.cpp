#include "cpu.h"

int CPU::getAcc() const
{
    return acc;
}

void CPU::setAcc(int value)
{
    if (value >= 0 && value < 16) {
        acc = value;
    } else {
        cerr << "Accumulator value can be 0-15. " << value << " is wrong value." << endl;
    }
}

int CPU::getCarry() const
{
    return carry;
}

void CPU::setCarry(int value)
{
    if (value == 1 || value == 0) {
        carry = value;
    } else {
        cerr << "Carry is a bit and can be 0 or 1. " << value << " is wrong value of a carry bit." << endl;
    }
}

int CPU::getTest() const
{
    return test;
}

void CPU::setTest(int value)
{
    if (value == 1 || value == 0) {
        test = value;
    } else {
        cerr << "Test is a bit and can be 0 or 1. " << value << " is wrong value of a test bit." << endl;
    }
}

int CPU::getCycles() const
{
    return cycles;
}

void CPU::setCycles(unsigned int value)
{
    cycles = value;
}

QString CPU::getOperation() const
{
    return operation;
}

void CPU::setOperation(const QString &value)
{
    operation = value;
}

Stack* CPU::getStack() const
{
    return stack;
}

vector<int> CPU::getRegisters() const
{
    return registers;
}

void CPU::setRegisters(int index, int value)
{

    if(!(index >= 0 && index <= 0xF)) {
        cerr << "Indexes of registers could be 0-15. " << index << " is wrong index." << endl;
        return;
    }

    if(value >= 0 && value <= 0xF) {
        cerr << "Register value could be 0-15. " << value << " is wrong value." << endl;
        return;
    }

    registers.at(index) = value;
}

vector<int> CPU::getPairs() const
{
    return pairs;
}

void CPU::setPairs(int index, int value)
{
    if(!(index >= 0 && index <= 7)) {
        cerr << "Indexes of pairs could be 0-7. " << index << " is wrong index." << endl;
        return;
    }

    if(value >= 0 && value <= 0xFF) {
        cerr << "Pair value could be 0-255. " << value << " is wrong value." << endl;
        return;
    }

    pairs.at(index) = value;
}

int CPU::getPC() const
{
    return PC;
}

void CPU::setPC(int value)
{
    if (value <= 0 || value > 0xFFFFFF) {
        std::cerr << "Program counter could be 0-0xFFFFFF. " << value << " is wrong value." << endl;
        return;
    }

    PC = value;
}

int CPU::getDcl() const
{
    return dcl;
}

void CPU::setDcl(int value)
{

    if(value >= 0 && value <= 0xFF) {
        cerr << "DCL value could be 0-255. " << value << " is wrong value." << endl;
        return;
    }

    dcl = value;
}

int CPU::getSrc() const
{
    return src;
}

void CPU::setSrc(int value)
{
    if(value >= 0 && value <= 0xFF) {
        cerr << "SRC value could be 0-255. " << value << " is wrong value." << endl;
        return;
    }

    src = value;
}

CPU::CPU()
{
    stack = new Stack;
    PC = 0;
    acc = 0;
    carry = 0;
    test = 0;
    cycles = 0;
    operation = "";
    dcl = 0;
    src = 0;

    for (int i = 0; i <= 7; i++) {
        pairs.push_back(0);
    }

    for (int i = 0; i <= 15; i++) {
        registers.push_back(0);
    }

}
