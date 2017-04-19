#include "line.h"

const std::regex Line::labelRegex = std::regex("[[:alpha:]][[:alnum:]]{2,}(,)");
const std::regex Line::commandRegex = std::regex("[[:alpha:]]{2,}[[:alnum:]]?");
const std::regex Line::paramsRegex = std::regex("([[:blank:]]+[[:print:]]+[[:blank:]]*)(,)?([[:blank:]]+[[:print:]]+[[:blank:]]*)?");
const std::regex Line::commentRegex = std::regex("/[[:print:]]*");
const std::regex Line::pseudoRegex = std::regex("[[:blank:]]*=[[:blank:]]+");

void Line::assertNotEmptyLine(const std::string& line, std::string parsedLine)
{
    if (!String::trim(parsedLine).empty())
    {
        std::string msg = "Line::There is an unknown parameter " + String::trimBeginEnd(parsedLine)
                + " in line " + String::trim(line);
        throw msg;
    }
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

    // Parsing pseudo
    SearchResult pseudo = String::search(parsedLine, pseudoRegex);
    if (!pseudo.isEmpty())
    {
        std::shared_ptr<Operand> operand = std::shared_ptr<Operand>(new Operand(pseudo.suffix, CommandSet::OperandType::ADDRESS));

        unsigned int address = operand->getCode();

        ObjectCode::setProgramCounter(address);

        assertNotEmptyLine(line, pseudo.prefix);
        return;
    }

    // parse label
    SearchResult label = String::search(parsedLine, labelRegex);
    if (!label.isEmpty())
    {
        std::string labelName = label.find;
        labelName = labelName.substr(0, labelName.size() - 1);
        std::string labelParam = String::trimBeginEnd(label.suffix);

        std::shared_ptr<Label>(new Label(labelName, labelParam));

        if (!String::trim(label.prefix).empty())
        {
            std::string msg = "Line::There is an unknown parameter " + label.prefix
                    + " in line " + String::trim(line);
            throw msg;
        }

        return;
    }

    // parse instruction
    SearchResult command = String::search(parsedLine, commandRegex);
    parsedLine = command.prefix + " " + command.suffix;

    SearchResult params = String::search(parsedLine, paramsRegex);
    parsedLine = params.prefix + " " + params.suffix;

    std::shared_ptr<Instruction> instruction = std::shared_ptr<Instruction>(
                new Instruction(String::trimBeginEnd(command.find),
                                String::trimBeginEnd(params.find)));

    ObjectCode::write(instruction->getCode());

    // here MUST be an empty parsedLine
    assertNotEmptyLine(line, parsedLine);
}

