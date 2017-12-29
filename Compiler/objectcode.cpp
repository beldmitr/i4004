#include "objectcode.h"

unsigned int ObjectCode::programCounter = 0;
std::vector<unsigned int> ObjectCode::table;

void ObjectCode::writeBigEndian(unsigned int hiByte, unsigned int lowByte)
{
    if (programCounter+1 < 0x1000)
    {
        table[programCounter] = hiByte;
        setProgramCounter(programCounter+1);
    }
    else
    {
        std::string msg = "Couldn't access to address 0x" + String::int2hex_string(programCounter + 1) + ". Allowed only 12 bit addresses";
        throw CompilerException("ObjectCode", msg);
    }

    if (programCounter+1 < 0x1001)
    {
        table[programCounter] = lowByte;
        setProgramCounter(programCounter+1);
    }
    else
    {
        std::string msg = "Couldn't access to address 0x" + String::int2hex_string(programCounter) + ". Allowed only 12 bit addresses";
        throw CompilerException("ObjectCode", msg);
    }
}

void ObjectCode::setProgramCounter(unsigned int address)
{
    if (address > 0x1000)  /// TODO magic number
    {
        std::string msg = "Couldn't set address 0x" + String::int2hex_string(address) + ". Allowed only 12 bit addresses";
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
        unsigned hiByte = (value & 0xFF00) >> 8;
        unsigned lowByte = (value & 0xFF);
        writeBigEndian(hiByte, lowByte);
    }
    else // write 1 byte length instruction
    {        
        if (programCounter+1 < 0x1001)
        {
            table[programCounter] = value; // only write
            setProgramCounter(programCounter+1); // next instruction will be written into the next address
        }
        else
        {
            std::string msg = "Couldn't access to address 0x" + String::int2hex_string(programCounter) + ". Allowed only 12 bit addresses";
            throw CompilerException("ObjectCode", msg);
        }
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
