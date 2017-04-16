#ifndef OPERAND_H
#define OPERAND_H

#include <regex>
#include <string>

#include "Compiler/pair.h"
#include "Compiler/register.h"
#include "Compiler/commandset.h"
#include "Compiler/labeltable.h"

class Operand
{
private:
    unsigned int code = 0;
    bool isEmpty = true;
public:
    Operand(const std::string& operand, CommandSet::OperandType type);




    unsigned int condition2code(const std::string& condition);
    unsigned int address2code(const std::string& address);
    unsigned int data2code(const std::string& data);

    bool getIsEmpty() const;
    unsigned int getCode() const;
};


#endif // OPERAND_H
