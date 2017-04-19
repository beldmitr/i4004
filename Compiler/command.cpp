#include "command.h"

std::string Command::getName() const
{
    return name;
}

unsigned int Command::getCode() const
{
    return code;
}

unsigned int Command::getLength() const
{
    return (code & 0xFF00) ? 2 : 1;
}

Command::Command(const std::string& command)
{
    this->code = CommandSet::getCode(command);
    this->name = command;
}
