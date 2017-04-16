#ifndef COMMANDSET_H
#define COMMANDSET_H

#include <map>
#include <string>

#include "Compiler/number.h"
#include "Utils/string.h"

class CommandSet
{
private:
    static std::map<std::string, std::string> set;

public:
    enum OperandType
    {
        NONE = 0,
        CONDITION = 'C',
        ADDRESS = 'A',
        DATA = 'D',
        PAIR = 'P',
        REGISTER = 'R'
    };

    static bool isCommand(const std::string& command);
    static std::string getRule(const std::string& command);
    static unsigned int getCommand(const std::string& command);
    static unsigned int getLength(const std::string& command);

    static unsigned int getNumberOperands(const std::string& command);

    static OperandType getOperandType(const std::string& command, unsigned int operandNumber);

};

#endif // COMMANDSET_H
