#ifndef OBJECTCODE_H
#define OBJECTCODE_H

#include <map>

class ObjectCode
{
public:
    enum Endianness
    {
        BigEndian,
        LittleEndian
    };
    static void setProgramCounter(unsigned int address);
    static void write(unsigned int value);
    static std::map<unsigned int, unsigned int> getTable();
    static unsigned int getProgramCounter();
    static void reset();

private:
    static Endianness endiannes;
    static unsigned int programCounter;
    static std::map<unsigned int, unsigned int> table;

    static void writeBigEndian(unsigned int hiByte, unsigned int lowByte);
    static void writeLittleEndian(unsigned int hiByte, unsigned int lowByte);
};

#endif // OBJECTCODE_H
