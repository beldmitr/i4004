#include "labeltable.h"

std::map<std::string, unsigned int> Instruction::LabelTable::table = std::map<std::string, unsigned int>();

void Instruction::LabelTable::add(const Label& label)
{
    /// TODO make an exception if inserted data is not unique
    table.insert(std::pair<std::string, unsigned int>(label.getName(), label.getValue()));
}

unsigned int Instruction::LabelTable::getByName(const std::string& name)
{
    /// TODO make and exception if there is no wanted label in the table
    return table[name];
}

void Instruction::LabelTable::clear()
{
    table.clear();
}
