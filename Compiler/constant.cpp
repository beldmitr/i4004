#include "constant.h"

std::regex Constant::constant = std::regex("[[:alpha:]][[:alnum:]]{2,}");

std::map<std::string, unsigned int> Constant::table = std::map<std::string, unsigned int>();

void Constant::add(const std::string name, unsigned int value)
{
    /// TODO decide if labels can be rewritten or it is an error to reassign a new value to a label.
    if (isConstantExist(name))
    {
        std::string msg = "Constant " + name + " is already defined. "
                + name + "=" + std::to_string(table[name]);
        throw CompilerException("Constant", msg);
    }

    table.insert({ name, value });
}

unsigned int Constant::getByName(const std::string& name)
{
    if (isConstantExist(name))
    {
        return table[name];
    }

    std::string msg = "Constant " + name + " doesn't exist";
    throw CompilerException("Constant", msg);
}

void Constant::clear()
{
    table.clear();
}

bool Constant::isConstantExist(const std::string& name)
{
    return (table.find(name) != table.end());
}

bool Constant::isConstant(const std::string& str)
{
    return regex_match(str, constant);
}
