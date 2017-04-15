#include "command.h"

std::string Command::getCommand() const
{
    return command;
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
    this->code = CommandSet::getCommand(command);
    this->command = command;
}
