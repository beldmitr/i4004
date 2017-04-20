#ifndef LINE_H
#define LINE_H

#include <regex>
#include <string>
#include <memory>

#include "Compiler/label.h"
#include "Compiler/instruction.h"
#include "Compiler/objectcode.h"

class Label;
class Instruction;

/**
 * @brief The Line class
 * This class parses a line of assembler code.
 * In line may occur Label, Instruction or Pseudo instruction =.
 *
 * The main aim of a class is to divide a gotten string
 * to label,instruction or pseudo instruction
 */
class Line
{
public:
    Line(const std::string& line);

    static const std::regex labelRegex; // Template for Label
    static const std::regex commandRegex; // Template for instruction, it is not exect
    static const std::regex paramsRegex; // Template for operands, for both - left and right
    static const std::regex commentRegex; // Template for comments
    static const std::regex pseudoRegex; // Template for pseudo instruction =
};

#endif // LINE_H
