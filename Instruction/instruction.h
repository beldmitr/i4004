#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <memory>

#include "command.h"
#include "params.h"

namespace Instruction {
    class Instruction
    {
    private:

        std::shared_ptr<::Instruction::Command> command;
        std::shared_ptr<::Instruction::Params> params;

    public:
        Instruction(const std::string& command, const std::string& operands);
        std::shared_ptr<::Instruction::Command> getCommand() const;
        std::shared_ptr<::Instruction::Params> getParams() const;
    };
}

#endif // INSTRUCTION_H
