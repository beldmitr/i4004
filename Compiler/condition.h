#ifndef CONDITION_H
#define CONDITION_H

#include <string>

#include "Compiler/number.h"
#include "Compiler/labeltable.h"
#include "Compiler/mathexpr.h"

class Condition
{
public:
    static unsigned int getUInt(const std::string& str);
};

#endif // CONDITION_H
