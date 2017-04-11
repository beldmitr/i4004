#include "line.h"

std::regex Utils::Assembler::Line::label = std::regex("[[:alpha:]][[:alnum:]]{2,}(,)");
std::regex Utils::Assembler::Line::instruction = std::regex("[[:alpha:]]{2,}[[:alnum:]]?");
std::regex Utils::Assembler::Line::operand = std::regex("([[:blank:]]+[[:print:]]+[[:blank:]]*)(,)?([[:blank:]]+[[:print:]]+[[:blank:]]*)?");
std::regex Utils::Assembler::Line::comment = std::regex("/[[:print:]]*");

bool Utils::Assembler::Line::isLabel(const std::string& str)
{
    return regex_match(str, label);
}

bool Utils::Assembler::Line::isInstruction(const std::string& str)
{
    return regex_match(str, instruction);
}

bool Utils::Assembler::Line::isOperand(const std::string& str)
{
    return regex_match(str, operand);
}

bool Utils::Assembler::Line::isComment(const std::string& str)
{
    return regex_match(str, comment);
}

bool Utils::Assembler::Line::searchLabel(const std::string& line, std::smatch& matchList)
{
    return regex_search(line, matchList, label);
}

bool Utils::Assembler::Line::searchInstruction(const std::string& line, std::smatch& matchList)
{
    return regex_search(line, matchList, instruction);
}

bool Utils::Assembler::Line::searchOperand(const std::string& line, std::smatch& matchList)
{
    return regex_search(line, matchList, operand);
}

bool Utils::Assembler::Line::searchComment(const std::string& line, std::smatch& matchList)
{
    return regex_search(line, matchList, comment);
}
