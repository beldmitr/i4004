#ifndef OBJECTCODE_H
#define OBJECTCODE_H

#include <map>

class ObjectCode
{
private:
    static unsigned int programCounter;
    static std::map<unsigned int, unsigned int> table;

public:
    static void setProgramCounter(unsigned int address);
    static void write(unsigned int value);
    static std::map<unsigned int, unsigned int> getTable();
};

#endif // OBJECTCODE_H
