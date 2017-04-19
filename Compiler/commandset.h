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

    class OperandStruct
    {
    public:
        const unsigned int position = 0;
        const unsigned int length = 0;
        const OperandType type = OperandType::NONE;

        OperandStruct& operator=(OperandStruct other)
        {
            const_cast<unsigned int&>(this->position) = other.position;
            const_cast<unsigned int&>(this->length) = other.length;
            const_cast<OperandType&>(this->type) = other.type;

            return *this;
        }

        OperandStruct(unsigned int position, unsigned int length, OperandType type)
        {
            const_cast<unsigned int&>(this->position) = position;
            const_cast<unsigned int&>(this->length) = length;
            const_cast<OperandType&>(this->type) = type;
        }
    };

    static bool isCommand(const std::string& command);
    static std::string getRule(const std::string& command);
    static unsigned int getCode(const std::string& command);
    static unsigned int getLength(const std::string& command);

    static unsigned int getNumberOperands(const std::string& command);
    static std::vector<OperandStruct> getOperands(const std::string& command);
    static OperandType getOperandType(const std::string& command, unsigned int operandNumber);

};

#endif // COMMANDSET_H
