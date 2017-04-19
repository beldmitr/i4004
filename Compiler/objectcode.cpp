#include "objectcode.h"

unsigned int ObjectCode::programCounter = 0;
std::map<unsigned int, unsigned int> ObjectCode::table;

void ObjectCode::setProgramCounter(unsigned int address)
{
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

        /// TODO Decide: write in BigEndian or SmallEndian

    }
    else // write 1 byte length instruction
    {
        table[programCounter] = value; // only write
        programCounter += 1;    // next instruction will be written into the next address
    }



}

std::map<unsigned int, unsigned int> ObjectCode::getTable()
{
    return table;
}
