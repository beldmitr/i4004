#include "stack.h"

int Stack::getActualPointer() const
{
    return actualPointer;
}

std::vector<int> Stack::getRegisters() const
{
    return registers;
}

Stack::Stack() : QObject()
{
    for (int i = 0; i < size; i++)
    {
        registers.push_back(0);
    }
}

Stack::~Stack()
{
    // delete or finalize here something
}

void Stack::write(int address)
{
    /*
     * Writing An Address To The Stack:
     *
     * To perform a stack write operation:
     * 1. The address is written into the register indicated by the pointer.
     * 2. The pointer is advanced to the next sequential register.
     *
     * Any register may be used to hold the first address written to the stack. More than
     * three addresses may be written to the stack; however, this will cause a corresponding
     * number of previously stored addresses to be overwritten and lost.
     * F.e. Storing the fourth address overwrites the first address stored.
     */
    if (address < 0 || address > 0xFFF)
    {
        std::cerr << "Wrong address is pushed to the Stack. Address can be [0x0 - 0xFFF]. Pushed address is "
                  << address << "." << std::endl;
        return;
    }
    registers[actualPointer] = address;

    actualPointer++;
    if (actualPointer >= size)
    {
        std::cerr << "Stack overflowed after writing." << std::endl;
        actualPointer = 0;
    }

    emit onStackChanged();
}

int Stack::read()
{
    /*
     * Reading An Address From The Stack:
     *
     * To perform a stack read operation:
     * 1. The pointer is backed up one register.
     * 2. The memory addres s indicated by the pointer is read.
     *
     * The address read remains in the stack undisturbed.
     */

    actualPointer--;
    if (actualPointer < 0)
    {
        std::cerr << "Stack underflowed after reading." << std::endl;
        actualPointer = size - 1;
    }

    emit onStackChanged();

    return registers[actualPointer] & 0xFFF;
}

void Stack::setPC(unsigned int value)
{
    if (value > 0xFFF)
    {
        std::cerr << "Program counter could be 0-0xFFFFFF. " << value
                  << " is wrong value." << std::endl;
        return;
    }

    registers[actualPointer] = value;

    emit onStackChanged();
}

unsigned int Stack::getPC()
{
    return registers[actualPointer] & 0xFFF;
}
