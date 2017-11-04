#include "params.h"

std::shared_ptr<Operand> Params::getOperand(unsigned int index) const
{
    if (index >= operands.size())
    {
        std::string msg = "Command expects the " + std::to_string(index + 1) + ". operand";
        throw CompilerException("Params", msg);
    }

    return operands[index];
}

std::string Params::getOperandString(unsigned int index) const
{
    if (index >= operands.size())
    {
        std::string msg = "Command expects the " + std::to_string(index + 1) + ". operand";
        throw CompilerException("Params", msg);
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

        if (str.empty() && type != CommandSet::OperandType::NONE)
        {
            std::string msg = "Command " + command + " expects the " + std::to_string(i+1)
                    + ". operand of " + CommandSet::operandTypeToString(type) + " type.";
            throw CompilerException("Params", msg);
        }

        operandsString.push_back(str);
        operands.push_back(std::shared_ptr<Operand>(new Operand(str, type)));
    }
}
