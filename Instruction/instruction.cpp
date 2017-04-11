#include "instruction.h"


std::shared_ptr<::Instruction::Command> Instruction::Instruction::getCommand() const
{
    return command;
}

std::shared_ptr<::Instruction::Params> Instruction::Instruction::getParams() const
{
    return params;
}

Instruction::Instruction::Instruction(const std::string& command, const std::string& operands)
{
    this->command = std::shared_ptr<::Instruction::Command>(new ::Instruction::Command(command));
    this->params = std::shared_ptr<::Instruction::Params>(new ::Instruction::Params(operands));
}

