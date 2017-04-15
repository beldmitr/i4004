#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "Utils/number.h"
#include "operand.h"
#include "labeltable.h"
#include "Utils/mathexpr.h"
#include "Utils/searchresult.h"

#include "Compiler/line.h"
#include "Compiler/instruction.h"

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
    std::string getName() const;
    unsigned int getValue() const;
};


#endif // LABEL_H
