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
    /// TODO
}

Instruction::Instruction(const std::string& command, const std::string& operands)
{
    this->command = std::shared_ptr<Command>(new Command(command));

    this->params = std::shared_ptr<Params>(new Params(command, operands));

    combine(); // combines command code and parameters codes
}

