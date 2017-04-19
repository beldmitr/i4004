#ifndef LINE_H
#define LINE_H

#include <iostream> /// TODO delete unused headers
#include <regex>
#include <string>
#include <memory>

//#include "Compiler/command.h"
//#include "Compiler/params.h"
#include "Compiler/label.h"
#include "Compiler/instruction.h"

class Label;
class Instruction;

class Line
{
private:
    std::shared_ptr<Label> label;
    std::shared_ptr<Instruction> instruction;

public:
    Line(const std::string& line);

    static const std::regex labelRegex; // Template for Label
    static const std::regex commandRegex; // Template for instruction, it is not exect
    static const std::regex paramsRegex; // Template for operands, for both - left and right
    static const std::regex commentRegex; // Template for comments
    std::shared_ptr<Instruction> getInstruction() const;
};

#endif // LINE_H
