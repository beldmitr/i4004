#ifndef LINE_H
#define LINE_H

#include <regex>
#include <string>
#include <memory>

#include "Compiler/label.h"
#include "Compiler/instruction.h"

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
    /**
     * @brief Line  - parser for Line. The main aim of the class is
     *                to find a Label or a pseudo instruction or an instruction,
     *                create instanties of them and to send the rest of the parameter
     *                line to the next classes, which will parse the rest of line on there level.
     * @param line  - a text line
     */
    /*
     * I exactly want here std::string, and NOT reference const std::string&,
     * because I make some changes with the line: deleting white spaces
     * and I don't want to make for this new variable.
     */
    Line(std::string line);

};

#endif // LINE_H
