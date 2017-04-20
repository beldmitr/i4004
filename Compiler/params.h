#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>

#include "Compiler/operand.h"
#include "Utils/string.h"

#include "Exceptions/compilerexception.h"

class Operand;

class Params
{
private:
    std::vector<std::shared_ptr<Operand>> operands;
    std::vector<std::string> operandsString;

public:
    Params(const std::string& command, const std::string& params);

    std::shared_ptr<Operand> getOperand(unsigned int index) const;
    std::string getOperandString(unsigned int index) const;
};

#endif // PARAMS_H
