#include "params.h"

std::shared_ptr<Instruction::Operand> Instruction::Params::getLeft() const
{
    return left;
}

std::shared_ptr<Instruction::Operand> Instruction::Params::getRight() const
{
    return right;
}

Instruction::Params::Params(const std::string& params)
{
    std::vector<std::string> operand = Utils::String::divideBy(params, ",");

    if (operand.size() > 2)
    {
        std::string msg = "Params::There are too much operands: ";
        for (std::string s : operand)
        {
            msg = msg + Utils::String::trimStrong(s) + " ";
        }
        throw msg;
    }

    left = std::shared_ptr<Operand>(new Operand(Utils::String::trimStrong(operand[0])));
    right = std::shared_ptr<Operand>(new Operand(Utils::String::trimStrong(operand[1])));
}


