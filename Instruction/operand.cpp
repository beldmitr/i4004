#include "operand.h"

std::regex Instruction::Operand::mathExpression = std::regex("([*]?[+-]?[[:alnum:]]+)+");
std::regex Instruction::Operand::pair = std::regex("[Pp][0-7]");
std::regex Instruction::Operand::reg = std::regex("[Rr]([0-9]|(1[0-6]))");
std::regex Instruction::Operand::label = std::regex("[[:alpha:]][[:alnum:]]{2,}");

bool Instruction::Operand::getIsEmpty() const
{
    return isEmpty;
}

unsigned int Instruction::Operand::getCode() const
{
    if (isEmpty)
    {
        std::string msg = "Operand::Operand is empty";
        throw msg;
    }
    return code;
}

Instruction::Operand::Operand(const std::string& operand)
{
    if (operand.empty())
    {
        // Do nothing. Operand is empty
    }
    else if (Utils::Number::isNumber(operand))
    {
        isEmpty = false;
        code = Utils::Number::getUInt(operand);
    }
    else if (isPair(operand))
    {
        isEmpty = false;
        code = Utils::Convert::pair2uint(operand);
    }
    else if (isRegister(operand))
    {
        isEmpty = false;
        code = Utils::Convert::register2uint(operand);
    }
    else if (isLabel(operand))
    {
        isEmpty = false;
         code = Instruction::LabelTable::getByName(operand);
    }
    else if (isMathExpression(operand))
    {
        isEmpty = false;
        code = Utils::MathExpr::evaluate(operand);

    }
    else
    {
        std::string msg = "Operand::Wrong type of operand " + operand;
        throw msg;
    }
}

bool Instruction::Operand::isPair(const std::string& str)
{
    return regex_match(str, pair);
}

bool Instruction::Operand::isRegister(const std::string& str)
{
    return regex_match(str, reg);
}

bool Instruction::Operand::isLabel(const std::string& str)
{
    return regex_match(str, label);
}

bool Instruction::Operand::isMathExpression(const std::string& str)
{
    return regex_match(str, mathExpression) && !isPair(str) && !isRegister(str) && !isLabel(str);
}

bool Instruction::Operand::searchPair(const std::string& str, std::smatch& matchList)
{
    return regex_search(str, matchList, pair);
}

bool Instruction::Operand::searchRegister(const std::string& str, std::smatch& matchList)
{
    return regex_search(str, matchList, reg);
}

bool Instruction::Operand::searchLabel(const std::string& str, std::smatch& matchList)
{
    return regex_search(str, matchList, label);
}

bool Instruction::Operand::searchMathExpression(const std::string& str, std::smatch& matchList)
{
    return regex_search(str, matchList, mathExpression);
}
