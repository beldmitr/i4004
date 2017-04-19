#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "Compiler/commandset.h"

class Command
{
private:
    std::string name;
    unsigned int code;

public:
    Command(const std::string& name);
    std::string getName() const;
    unsigned int getCode() const;
    unsigned int getLength() const;
};


#endif // COMMAND_H
