#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

using namespace std;

class Instruction
{
public:
    string name;
    string operandLeft;
    string operandRight;
    string line;
    int lineNumber;
    int code;

public:
    Instruction(string name, string operandLeft, string operandRight, string line, int lineNumber, int code);
};

#endif // INSTRUCTION_H
