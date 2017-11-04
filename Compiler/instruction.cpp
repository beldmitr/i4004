#include "instruction.h"


std::shared_ptr<Command> Instruction::getCommand() const
{
    return command;
}

std::shared_ptr<Params> Instruction::getParams() const
{
    return params;
}

unsigned int Instruction::getCode() const
{
    return code;
}

void Instruction::combine()
{
    std::string name = this->command->getName();

    std::string rule = CommandSet::getRule(name);
    std::vector<CommandSet::OperandStruct> ruleOperands = CommandSet::getOperands(name);

    unsigned int i = 0;
    for (CommandSet::OperandStruct o : ruleOperands)
    {
        std::shared_ptr<Operand> operand = this->params->getOperand(i);
        unsigned int operandCode = operand->getCode();

        // It is all right in if condition. There must be right shift (>>).
        if (operandCode >> o.length)
        {
            std::string operandString = this->getParams()->getOperandString(i);
            std::string msg = "Operand " + operandString + " has too big size. "
                    + "It is allowed only " + std::to_string(o.length) + " bits.";
            throw CompilerException("Instruction", msg);
        }

        for (unsigned int j = 0; j < o.length; j++)
        {
            unsigned int position = rule.length() - o.position - 1 - j;
            std::string bit = std::to_string(((1 << j) & operandCode) >> j);

            std::string left = rule.substr(0, position);
            std::string right = rule.substr(position + 1, rule.size() - 1);

            rule = left.append(bit).append(right);
        }

        i++;
    }

    rule = "0b" + rule;

    this->code = Number::getUInt(rule);
}

Instruction::Instruction(const std::string& command, const std::string& operands)
{
    this->command = std::shared_ptr<Command>(new Command(command));

    this->params = std::shared_ptr<Params>(new Params(command, operands));

    combine(); // combines command code and parameters' codes
}

