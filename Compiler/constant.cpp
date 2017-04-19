#include "constant.h"

std::regex Constant::label = std::regex("[[:alpha:]][[:alnum:]]{2,}");

std::map<std::string, unsigned int> Constant::table = std::map<std::string, unsigned int>();

void Constant::add(const std::string name, unsigned int value)
{
    /// TODO decide if labels can be rewritten or it is an error to reassign a new value to a label.
    if (isConstantExist(name))
    {
        std::string msg = "Constant::Constant " + name + " is already defined. "
                + name + "=" + std::to_string(table[name]);
        throw msg;
    }

    table.insert({ name, value });
}

unsigned int Constant::getByName(const std::string& name)
{
    if (isConstantExist(name))
    {
        return table[name];
    }

    std::string msg = "Constant::Constant " + name + " doesn't exist";
    throw msg;
}

void Constant::clear()
{
    table.clear();
}

bool Constant::isConstantExist(const std::string& name)
{
    return (table.find(name) != table.end());
}

bool Constant::isLabel(const std::string& str)
{
    return regex_match(str, label);
}
