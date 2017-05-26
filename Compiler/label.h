#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "Compiler/constant.h"
#include "Utils/searchresult.h"

#include "Compiler/mathexpr.h"
#include "Compiler/line.h"
#include "Compiler/instruction.h"
#include "Compiler/number.h"

class Label
{
private:
    std::shared_ptr<Instruction> instruction;

    std::string name;
    unsigned int value;

public:
    /*
     * In this case, value might be an address.
     * Because if it is a number, it will be as std::string
     */
    Label(const std::string& name, unsigned int value);

    Label(const std::string& name, const std::string& param);

    static bool isLabel(const std::string& str);

    std::string getName() const;
    unsigned int getValue() const;
    std::shared_ptr<Instruction> getInstruction() const;
};


#endif // LABEL_H
