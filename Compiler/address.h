#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

#include "Compiler/number.h"
#include "Compiler/constant.h"
#include "Compiler/mathexpr.h"

class Address
{
public:
    static unsigned int getUInt(const std::string& addr);

};

#endif // ADDRESS_H
