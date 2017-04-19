#include "line.h"

const std::regex Line::labelRegex = std::regex("[[:alpha:]][[:alnum:]]{2,}(,)");
const std::regex Line::commandRegex = std::regex("[[:alpha:]]{2,}[[:alnum:]]?");
const std::regex Line::paramsRegex = std::regex("([[:blank:]]+[[:print:]]+[[:blank:]]*)(,)?([[:blank:]]+[[:print:]]+[[:blank:]]*)?");
const std::regex Line::commentRegex = std::regex("/[[:print:]]*");

/*
 * Line may be a Label or an Instruction
 */

std::shared_ptr<Instruction> Line::getInstruction() const
{
    if (instruction)
    {
        return instruction;
    }
    else if (label)
    {
        return label->getInstruction();
    }
    else
    {
        std::string msg = "Line::Wrong instruction";
        throw msg;
    }

}

Line::Line(const std::string& line)
{
    std::string parsedLine = line;

    // search for
    SearchResult label = String::search(parsedLine, labelRegex);
    SearchResult command = String::search(parsedLine, commandRegex);
    SearchResult params = String::search(parsedLine, paramsRegex);
    SearchResult comment = String::search(parsedLine, commentRegex);

    // Parsing a comment
    if (!comment.isEmpty())
    {
        // we don't need a comment, so for next parsing we will take a line before a comment
        parsedLine = comment.prefix;
    }

    if (!label.isEmpty())
    {
        std::string labelName = label.find;
        labelName = labelName.substr(0, labelName.size() - 1);
        std::string labelParam = String::trimBeginEnd(label.suffix);

        this->label = std::shared_ptr<Label>(new Label(labelName, labelParam));

        if (!String::trim(label.prefix).empty())
        {
            std::string msg = "Line::There is an unknown parameter " + label.prefix
                    + " in line " + String::trim(line);
            throw msg;
        }

        return;
    }
    else
    {

        parsedLine = command.prefix + " " + command.suffix;


        parsedLine = params.prefix + " " + params.suffix;

        this->instruction = std::shared_ptr<Instruction>(
                    new Instruction(String::trimBeginEnd(command.find),
                                    String::trimBeginEnd(params.find)));

        Address::setActual(Address::getActual() + this->instruction->getCommand()->getLength());
    }

    // here MUST be an empty parsedLine
    if (!String::trim(parsedLine).empty())
    {
        std::string msg = "Line::There is an unknown parameter " + String::trimStrong(parsedLine)
                + " in line " + String::trim(line);
        throw msg;
    }

}

