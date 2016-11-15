#include "instruction.h"

Instruction::Instruction(string name, string operandLeft, string operandRight, string line, int lineNumber, int code)
    : name(name), operandLeft(operandLeft), operandRight(operandRight), line(line), lineNumber(lineNumber), code(code)
{

}
