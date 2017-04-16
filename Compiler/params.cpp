#include "params.h"

std::shared_ptr<Operand> Params::getOperand(unsigned int index) const
{
    if (index > operands.size())
    {
        std::string msg = "Params::There is no " + std::to_string(index) + " operand";
        throw msg;
    }

    return operands[index];
}

Params::Params(const std::string& command, const std::string& params)
{
    std::vector<std::string> operand = String::divideBy(params, ",");

    if (operand.size() > CommandSet::getNumberOperands(command))
    {
        std::string msg = "Params::There are too much operands: ";
        for (std::string s : operand)
        {
            msg = msg + String::trimStrong(s) + " ";
        }
        throw msg;
    }

    for (int i = 0; i < operand.size(); i++)
    {
        std::string str = String::trimBeginEnd(operand[i]);
        CommandSet::OperandType type = CommandSet::getOperandType(command, i);

        operands.push_back(std::shared_ptr<Operand>(new Operand(str, type)));
    }
}
