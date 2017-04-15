#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>

#include "Compiler/operand.h"
#include "Utils/string.h"

class Operand;

class Params
{
private:
    std::vector<std::shared_ptr<Operand>> operands;

public:
    Params(const std::string& command, const std::string& params);

    std::shared_ptr<Operand> getOperand(unsigned int index) const;
};

#endif // PARAMS_H
