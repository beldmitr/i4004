#include "operand.h"

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
            this->code = Pair::getUInt(operand);
            break;
        case CommandSet::OperandType::REGISTER:
            this->code = Register::getUInt(operand);
            break;
        default:
            std::string msg = "Operand::Unknown type " + std::to_string((char)type) + " of the operand " + operand;
            throw msg;
    }
}

unsigned int Operand::condition2code(const std::string& condition)
{
    if (Number::isNumber(condition))
    {
        isEmpty = false;
        code = Number::getUInt(condition);
    }
    else if (Pair::isPair(condition))
    {
        isEmpty = false;
        code = Pair::getUInt(condition);
    }
    else if (Register::isRegister(condition))
    {
        isEmpty = false;
        code = Register::getUInt(condition);
    }
    else if (Label::isLabel(condition))
    {
        isEmpty = false;
         code = LabelTable::getByName(condition);
    }
    else if (MathExpr::isMathExpression(condition))
    {
        isEmpty = false;
        code = MathExpr::evaluate(condition);
    }
    else
    {
        std::string msg = "Operand::Wrong type of condition " + condition;
        throw msg;
    }
}

unsigned int Operand::address2code(const std::string& address)
{

}

unsigned int Operand::data2code(const std::string& data)
{

}



