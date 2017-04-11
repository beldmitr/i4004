#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "Instruction/commandset.h"

namespace Instruction
{
    class Command
    {
    private:
        std::string command;
        unsigned int code;

    public:
        Command(const std::string& command);
        std::string getCommand() const;
        unsigned int getCode() const;
        unsigned int getLength() const;
    };
}

#endif // COMMAND_H
