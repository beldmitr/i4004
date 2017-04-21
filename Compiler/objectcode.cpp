#include "objectcode.h"

ObjectCode::Endianness ObjectCode::endiannes = ObjectCode::Endianness::BigEndian;
unsigned int ObjectCode::programCounter = 0;
std::vector<unsigned int> ObjectCode::table;

void ObjectCode::writeBigEndian(unsigned int hiByte, unsigned int lowByte)
{
    table[programCounter] = hiByte;
    programCounter += 1;
    table[programCounter] = lowByte;
    programCounter += 1;
}

void ObjectCode::writeLittleEndian(unsigned int hiByte, unsigned int lowByte)
{
    table[programCounter] = lowByte;
    programCounter += 1;
    table[programCounter] = hiByte;
    programCounter += 1;
}

void ObjectCode::setProgramCounter(unsigned int address)
{
    if (address > 0xFFF)  /// TODO magic number
    {
        std::string msg = "Address " + std::to_string(address) + " is too big. Allowed only 12 bit addresses";
        throw CompilerException("ObjectCode", msg);
    }
    programCounter = address;
}

void ObjectCode::write(unsigned int value)
{
    // check, the number must be less then 2 bytes
    if (value > 0xFFFF)
    {
        std::string msg = "Value " + std::to_string(value) + " is too big.";
        throw CompilerException("ObjectCode", msg);
    }

    // write a 2 byte length instruction
    if (value & 0xFF00)
    {
        // divide to 2 bytes and write each byte on the needed address
        unsigned int hiByte = (value & 0xFF00) >> 8;
        unsigned int lowByte = (value & 0xFF);
        if (endiannes == Endianness::BigEndian)
        {
            writeBigEndian(hiByte, lowByte);
        }
        else
        {
            writeLittleEndian(hiByte, lowByte);
        }

    }
    else // write 1 byte length instruction
    {
        table[programCounter] = value; // only write
        programCounter += 1;    // next instruction will be written into the next address
    }

    if (programCounter > 0xFFF)  /// TODO magic number
    {
        programCounter = 0;
    }
}

std::vector<unsigned int> ObjectCode::getTable()
{
    return table;
}

unsigned int ObjectCode::getProgramCounter()
{
    return programCounter;
}

void ObjectCode::reset()
{
    programCounter = 0;
    table.clear();
    table.resize(0x1000);
}
