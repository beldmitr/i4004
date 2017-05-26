#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <memory>

#include "command.h"
#include "params.h"

class Params;

class Instruction
{
private:
    std::shared_ptr<Command> command;
    std::shared_ptr<Params> params;

    unsigned int code;

    void combine();

public:
    Instruction(const std::string& command, const std::string& operands);
    std::shared_ptr<Command> getCommand() const;
    std::shared_ptr<Params> getParams() const;
    unsigned int getCode() const;
};


#endif // INSTRUCTION_H
