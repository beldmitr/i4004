#include "label.h"

std::regex Label::label = std::regex("[[:alpha:]][[:alnum:]]{2,}");

Label::Label(const std::string& name, unsigned int value)
{
    this->name = name;
    this->value = value;
}

Label::Label(const std::string& name, const std::string& param)
{
    this->name = name;

    SearchResult command = String::search(param, Line::commandRegex);
    if (!command.isEmpty() && CommandSet::isCommand(command.find))
    {
        SearchResult params = String::String::search(param, Line::paramsRegex);
        instruction = std::shared_ptr<Instruction>(new Instruction(command.find, params.find));
        this->value = instruction->getCode();

        Constant::add(this->name, Address::getActual());
    }
    else if (Number::isNumber(param))
    {
        this->value = Number::getUInt(param);
        Constant::add(this->name, this->value);
    }
    else if (Label::isLabel(param))
    {
        this->value = Constant::getByName(param);
        Constant::add(this->name, this->value);
    }
    else if (MathExpr::isMathExpression(param))
    {
        this->value = MathExpr::evaluate(param);
        Constant::add(this->name, this->value);
    }
    else
    {
        std::string msg = "Label::Wrong parameter " + param + " in label " + name;
        throw msg;
    }
}


bool Label::isLabel(const std::string& str)
{
    return regex_match(str, label);
}

std::string Label::getName() const
{
    return name;
}

unsigned int Label::getValue() const
{
    return value;
}
