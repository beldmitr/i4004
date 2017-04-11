#include "label.h"

std::string Instruction::Label::getName() const
{
    return name;
}

unsigned int Instruction::Label::getValue() const
{
    return value;
}

Instruction::Label::Label(const std::string& name, unsigned int value)
{
    this->name = name;
    this->value = value;
}

Instruction::Label::Label(const std::string& name, const std::string& param)
{
    this->name = name;

    if (Utils::Number::isNumber(param))
    {
        this->value = Utils::Number::getUInt(param);
    }
    else if (Instruction::Operand::isLabel(param))
    {
        this->value = Instruction::LabelTable::getByName(param);
    }
    else if (Instruction::Operand::isMathExpression(param))
    {
        this->value = Utils::MathExpr::evaluate(param);
    }
    else
    {
        std::string msg = "Label::Wrong parameter " + param + " in label " + name;
        throw msg;
    }
}
