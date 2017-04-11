#include "command.h"

std::string Instruction::Command::getCommand() const
{
    return command;
}

unsigned int Instruction::Command::getCode() const
{
    return code;
}

unsigned int Instruction::Command::getLength() const
{
    return (code & 0xFF00) ? 2 : 1;
}

Instruction::Command::Command(const std::string& command)
{
    this->code = CommandSet::getCommand(command);
    this->command = command;
}
