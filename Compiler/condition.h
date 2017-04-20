#ifndef CONDITION_H
#define CONDITION_H

#include <string>

#include "Compiler/number.h"
#include "Compiler/constant.h"
#include "Compiler/mathexpr.h"

#include "Exceptions/compilerexception.h"

class Condition
{
public:
    static unsigned int getUInt(const std::string& str);
};

#endif // CONDITION_H
