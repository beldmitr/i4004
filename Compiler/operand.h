#ifndef OPERAND_H
#define OPERAND_H

#include <regex>
#include <string>

#include "Compiler/commandset.h"
#include "Compiler/data.h"
#include "Compiler/condition.h"


class Operand
{
private:
    unsigned int code = 0;
    bool isEmpty = true;
public:
    Operand(const std::string& operand, CommandSet::OperandType type);

    bool getIsEmpty() const;
    unsigned int getCode() const;
};


#endif // OPERAND_H
