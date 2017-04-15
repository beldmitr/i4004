#include "line.h"

const std::regex Line::labelRegex = std::regex("[[:alpha:]][[:alnum:]]{2,}(,)");
const std::regex Line::commandRegex = std::regex("[[:alpha:]]{2,}[[:alnum:]]?");
const std::regex Line::paramsRegex = std::regex("([[:blank:]]+[[:print:]]+[[:blank:]]*)(,)?([[:blank:]]+[[:print:]]+[[:blank:]]*)?");
const std::regex Line::commentRegex = std::regex("/[[:print:]]*");

/*
 * Line may be a Label or an Instruction
 */

unsigned int Line::getCode() const
{
    return code;
}

Line::Line(const std::string& line)
{
    std::string parsedLine = line;

    // Parsing a comment
    SearchResult comment = String::search(parsedLine, commentRegex);
    if (!comment.isEmpty())
    {
        // we don't need a comment, so for next parsing we will take a line before a comment
        parsedLine = comment.prefix;
    }

    // Parsing a label
    SearchResult label = String::search(parsedLine, labelRegex);
    if (!label.isEmpty())
    {
        this->label = std::shared_ptr<Label>(new Label(label.find, label.suffix));
        code = this->label->getValue();

        return;
    }
    else
    {
        SearchResult command = String::search(parsedLine, commandRegex);
        parsedLine = command.prefix + " " + command.suffix;

        SearchResult params = String::search(parsedLine, paramsRegex);
        parsedLine = params.prefix + " " + params.suffix;

        this->instruction = std::shared_ptr<Instruction>(new Instruction(command.find, params.find));
        this->code = this->instruction->getCode();
    }

    // here MUST be an empty parsedLine
    if (!String::trim(parsedLine).empty())
    {
        std::string msg = "There is an unknown parameter " + String::trimStrong(parsedLine)
                + "in line " + String::trim(line);
        throw msg;
    }

}

