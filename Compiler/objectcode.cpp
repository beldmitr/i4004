#include "objectcode.h"

ObjectCode::Endianness ObjectCode::endiannes = ObjectCode::Endianness::BigEndian;
unsigned int ObjectCode::programCounter = 0;
std::map<unsigned int, unsigned int> ObjectCode::table;

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
        std::string msg = "ObjectCode::Address " + std::to_string(address) + " is too big. Allowed only 12 bit addresses";
        throw msg;
    }
    programCounter = address;
}

void ObjectCode::write(unsigned int value)
{
    // check if the number is less then 2 bytes
    if (value & 0xFFFF)
    {
        std::string msg = "ObjectCode::Value " + std::to_string(value) + " is too big.";
        throw msg;
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

std::map<unsigned int, unsigned int> ObjectCode::getTable()
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
}
