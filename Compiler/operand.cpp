#include "operand.h"

std::regex Operand::mathExpression = std::regex("([*]?[+-]?[[:alnum:]]+)+");
std::regex Operand::pair = std::regex("[Pp][0-7]");
std::regex Operand::reg = std::regex("[Rr]([0-9]|(1[0-6]))");
std::regex Operand::label = std::regex("[[:alpha:]][[:alnum:]]{2,}");

bool Operand::getIsEmpty() const
{
    return isEmpty;
}

unsigned int Operand::getCode() const
{
    if (isEmpty)
    {
        std::string msg = "Operand::Operand is empty";
        throw msg;
    }
    return code;
}

Operand::Operand(const std::string& operand, CommandSet::OperandType type)
{
    switch(type)
    {
        case CommandSet::OperandType::CONDITION:
            this->code = condition2code(operand);
            break;
        case CommandSet::OperandType::ADDRESS:
            this->code = address2code(operand);
            break;
        case CommandSet::OperandType::DATA:
            this->code = data2code(operand);
            break;
        case CommandSet::OperandType::PAIR:
            this->code = pair2code(operand);
            break;
        case CommandSet::OperandType::REGISTER:
            this->code = register2code(operand);
            break;
        default:
            std::string msg = "Operand::Unknown type " + std::to_string((char)type) + " of the operand " + operand;
            throw msg;
    }
}

bool Operand::isPair(const std::string& str)
{
    return regex_match(str, pair);
}

bool Operand::isRegister(const std::string& str)
{
    return regex_match(str, reg);
}

bool Operand::isLabel(const std::string& str)
{
    return regex_match(str, label);
}

bool Operand::isMathExpression(const std::string& str)
{
    return regex_match(str, mathExpression) && !isPair(str) && !isRegister(str) && !isLabel(str);
}

unsigned int Operand::condition2code(const std::string& condition)
{
//    if (Number::isNumber(operand))
//    {
//        isEmpty = false;
//        code = Number::getUInt(operand);
//    }
//    else if (isPair(operand))
//    {
//        isEmpty = false;
//        code = Convert::pair2uint(operand);
//    }
//    else if (isRegister(operand))
//    {
//        isEmpty = false;
//        code = Convert::register2uint(operand);
//    }
//    else if (isLabel(operand))
//    {
//        isEmpty = false;
//         code = LabelTable::getByName(operand);
//    }
//    else if (isMathExpression(operand))
//    {
//        isEmpty = false;
//        code = MathExpr::evaluate(operand);
//    }
//    else
//    {
//        std::string msg = "Operand::Wrong type of operand " + operand;
//        throw msg;
//    }
}

unsigned int Operand::address2code(const std::string& address)
{

}

unsigned int Operand::data2code(const std::string& data)
{

}

unsigned int Operand::pair2code(const std::string& pair)
{

}

unsigned int Operand::register2code(const std::__cxx11::string& reg)
{

}
