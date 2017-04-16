#include "labeltable.h"

std::map<std::string, unsigned int> LabelTable::table = std::map<std::string, unsigned int>();

void LabelTable::add(const Label& label)
{
    std::string name = label.getName();

    /// TODO decide if labels can be rewritten or it is an error to reassign something to a label.
    if (isLabelExist(name))
    {
        std::string msg = "LabelTable::Label " + name + " is already defined. "
                + name + "=" + std::to_string(table[name]);
        throw msg;
    }

    table.insert(std::pair<std::string, unsigned int>(name, label.getValue()));
}

unsigned int LabelTable::getByName(const std::string& name)
{
    if (isLabelExist(name))
    {
        return table[name];
    }

    std::string msg = "Labeltable::Label " + name + " doesn't exist";
    throw msg;
}

void LabelTable::clear()
{
    table.clear();
}

bool LabelTable::isLabelExist(const std::string& name)
{
    return (table.find(name) != table.end());
}
