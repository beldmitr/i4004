#include "operand.h"

bool Operand::getIsEmpty() const
{
    return isEmpty;
}

unsigned int Operand::getCode() const
{
    if (isEmpty)
    {
        std::string msg = "Operand is empty";
        throw CompilerException("Operand", msg);
    }
    return code;
}

Operand::Operand(const std::string& operand, CommandSet::OperandType type)
{
    switch(type)
    {
        case CommandSet::OperandType::CONDITION:
            this->code = Condition::getUInt(operand);
            isEmpty = false;
            break;
        case CommandSet::OperandType::ADDRESS:
            this->code = Address::getUInt(operand);
            isEmpty = false;
            break;
        case CommandSet::OperandType::DATA:
            this->code = Data::getUInt(operand);
            isEmpty = false;
            break;
        case CommandSet::OperandType::PAIR:
            this->code = Pair::getUInt(operand);
            isEmpty = false;
            break;
        case CommandSet::OperandType::REGISTER:
            this->code = Register::getUInt(operand);
            isEmpty = false;
            break;
        default:
            std::string msg = "Unknown type " + std::to_string((char)type) + " of the operand " + operand;
            throw CompilerException("Operand", msg);
    }
}
