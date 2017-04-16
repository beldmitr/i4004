#ifndef DATA_H
#define DATA_H

#include <string>

#include "Compiler/number.h"
#include "Compiler/mathexpr.h"
#include "Compiler/labeltable.h"

class Data
{
public:
    static unsigned int getUInt(const std::string& data);
};

#endif // DATA_H
