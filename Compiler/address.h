#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

#include "Compiler/number.h"
#include "Compiler/labeltable.h"
#include "Compiler/mathexpr.h"

class Address
{
private:
    unsigned int actual = 0;
public:
    static unsigned int getUInt(const std::string& addr);

    unsigned int getActual() const; // is a star sign (*) in assembler
    void setActual(unsigned int value); // is an equal sign (=) in assembler
};

#endif // ADDRESS_H
