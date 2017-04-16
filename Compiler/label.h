#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "operand.h"
#include "labeltable.h"
#include "Utils/searchresult.h"

#include "Compiler/mathexpr.h"
#include "Compiler/line.h"
#include "Compiler/instruction.h"
#include "Compiler/number.h"

class Label
{
private:
    /*
     * Check label in operand, do not be confused with regex label in Assembler::Line,
     * which check or find a label in line.
     * They are different:
     *
     * in line a label is with a comma, f.e.
     *      ABC, 45
     *      LABEL, FIM P1, 0x0
     * BUT
     * in an operand it is without comma, f.e.
     *      FIM P2, ABC+2
     *
     */
    static std::regex label;

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
};


#endif // LABEL_H
