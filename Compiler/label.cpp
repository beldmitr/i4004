#include "label.h"

std::string Label::getName() const
{
    return name;
}

unsigned int Label::getValue() const
{
    return value;
}

Label::Label(const std::string& name, unsigned int value)
{
    this->name = name;
    this->value = value;
}

Label::Label(const std::string& name, const std::string& param)
{
    this->name = name;

    SearchResult command = String::search(param, Line::commandRegex);
    if (!command.isEmpty())
    {
        SearchResult params = String::search(param, Line::paramsRegex);
        instruction = std::shared_ptr<Instruction>(new Instruction(command.find, params.find));


    }
    else if (Number::isNumber(param))
    {
        this->value = Number::getUInt(param);
    }
    else if (Operand::isLabel(param))
    {
        this->value = LabelTable::getByName(param);
    }
    else if (Operand::isMathExpression(param))
    {
        this->value = MathExpr::evaluate(param);
    }
    else
    {
        std::string msg = "Label::Wrong parameter " + param + " in label " + name;
        throw msg;
    }
}
