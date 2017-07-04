#include "cpu.h"

int CPU::getCountRegisters() const
{
    return countRegisters;
}

CPU::CPU() : QObject()
{
    stack = std::shared_ptr<Stack>(new Stack);
    acc = 0;
    carry = 0;
    test = 0;
    cycles = 0;
    operation = "";
    dcl = 0;
    src = 0;

    for (int i = 0; i < countRegisters; i++)
    {
        registers.push_back(0);
    }

}

CPU::~CPU()
{
    // delete or finalize here something
}

int CPU::getAcc() const
{
    return acc;
}

void CPU::setAcc(unsigned int value)
{
    if (value <= 0xF)
    {
        acc = value;
        emit onCpuChanged();
    }
    else
    {
        std::cerr << "Accumulator value can be 0-15. " << value
                  << " is wrong value." << std::endl;
    }
}

int CPU::getCarry() const
{
    return carry;
}

void CPU::setCarry(unsigned int value)
{
    if (value == 1 || value == 0)
    {
        carry = value;
        emit onCpuChanged();
    }
    else
    {
        std::cerr << "Carry is a bit and can be 0 or 1. " << value
             << " is wrong value of a carry bit." << std::endl;
    }
}

int CPU::getTest() const
{
    return test;
}

void CPU::setTest(unsigned int value)
{
    if (value == 1 || value == 0)
    {
        test = value;

        emit onCpuChanged();
    }
    else
    {
        std::cerr << "Test is a bit and can be 0 or 1. " << value
                  << " is wrong value of a test bit." << std::endl;
    }
}

int CPU::getCycles() const
{
    return cycles;
}

void CPU::setCycles(unsigned int value)
{
    cycles = value;
    emit onCpuChanged();
}

QString CPU::getOperation() const
{
    return operation;
}

void CPU::setOperation(const QString &value)
{
    operation = value;

    emit onCpuChanged();
}

Stack* CPU::getStack() const
{
    return stack.get();
}

unsigned int CPU::getRegisterAt(unsigned int index) const
{
    if(index >= countRegisters)
    {
        std::cerr << "Indexes of registers could be 0-15. " << index
                  << " is wrong index." << std::endl;
        throw QString("Indexes of registers could be 0-15. ")
                .append(QString::number(index))
                .append(" is wrong index.").toStdString();
    }

    return registers.at(index);
}

void CPU::setRegisters(unsigned int index, unsigned int value)
{

    if(index >= countRegisters)
    {
        std::cerr << "Indexes of registers could be 0-15. " << index
                  << " is wrong index." << std::endl;
        return;
    }

    if(value > 0xF)
    {
        std::cerr << "Register value could be 0-15. " << value
                  << " is wrong value." << std::endl;
        return;
    }

    registers.at(index) = value;

    emit onCpuChanged();
}

unsigned int CPU::getPairAt(unsigned int index) const
{
    if(index > 7)
    {
        std::cerr << "Indexes of pairs could be 0-7. " << index
                  << " is wrong index." << std::endl;
        throw QString("Indexes of pairs could be 0-7. ")
                .append(QString::number(index))
                .append(" is wrong index.").toStdString();
    }

    unsigned int registerLow = getRegisterAt(2*index);
    unsigned int registerHigh = getRegisterAt(2*index + 1);

    return (registerHigh << 4) | registerLow;
}

void CPU::setPairs(unsigned int index, unsigned int value)
{
    if(index > 7)
    {
        std::cerr << "Indexes of pairs could be 0-7. " << index
                  << " is wrong index." << std::endl;
        return;
    }

    if(value > 0xFF)
    {
        std::cerr << "Pair value could be 0-255. " << value
                  << " is wrong value." << std::endl;
        return;
    }

    this->setRegisters(2*index, (value & 0xF0) >> 4);
    this->setRegisters(2*index + 1, value & 0xF);

    emit onCpuChanged();
}

int CPU::getPC() const
{
    return stack->getPC();
}

void CPU::setPC(unsigned int value)
{
    stack->setPC(value);
}

int CPU::getDcl() const
{
    return dcl;
}

void CPU::setDcl(unsigned int value)
{
    if(value > 0xFF)
    {
        std::cerr << "DCL value could be 0-255. " << value
                  << " is wrong value." << std::endl;
        return;
    }

    dcl = value;

    emit onCpuChanged();
}

int CPU::getSrc() const
{
    return src;
}

void CPU::setSrc(unsigned int value)
{
    if(value > 0xFF)
    {
        std::cerr << "SRC value could be 0-255. " << value
                  << " is wrong value." << std::endl;
        return;
    }

    src = value;

    emit onCpuChanged();
}
