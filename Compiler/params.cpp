#include "params.h"

std::shared_ptr<Operand> Params::getOperand(unsigned int index) const
{
    if (index >= operands.size())
    {
        std::string msg = "Program expects " + std::to_string(index + 1) + " operand";
        throw CompilerException("Params", msg);
    }

    return operands[index];
}

std::string Params::getOperandString(unsigned int index) const
{
    if (index >= operands.size())
    {
        std::string msg = "Program expects " + std::to_string(index + 1) + " operand";
        throw CompilerException("Params", msg);;
    }

    return operandsString[index];
}

Params::Params(const std::string& command, const std::string& params)
{
    std::vector<std::string> operand = String::divideBy(params, ",");

    for (unsigned int i = 0; i < operand.size(); i++)
    {
        std::string str = String::trimBeginEnd(operand[i]);
        CommandSet::OperandType type = CommandSet::getOperandType(command, i);

        operandsString.push_back(str);
        operands.push_back(std::shared_ptr<Operand>(new Operand(str, type)));
    }
}
