#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

#include "Compiler/number.h"
#include "Compiler/constant.h"
#include "Compiler/mathexpr.h"

class Address
{
private:
    static unsigned int actual;
public:
    static unsigned int getUInt(const std::string& addr);

    static unsigned int getActual(); // is a star sign (*) in assembler
    static void setActual(unsigned int value); // is an equal sign (=) in assembler
};

#endif // ADDRESS_H
