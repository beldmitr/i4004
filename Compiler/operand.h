#ifndef OPERAND_H
#define OPERAND_H

#include <regex>
#include <string>

#include "Compiler/commandset.h"
#include "Compiler/labeltable.h"
#include "Utils/convert.h"
#include "Utils/number.h"
#include "Utils/mathexpr.h"

class Operand
{
private:
    /*
         *  rOpExpr not exact, always should be controlled on other regex.
         *  If it is not a pair, register, label and so on, only in this case we may say, that it is a mathematical expression.
         *  In other case we says, that it is not an expression
         *  For example:
         *  If rOpExpr equals true and other regex are false, we say that it is an expression.
         *  If rOpExpr equals true and for example rOpPair is true, then rOpPair has greater priority and we say that it is a pair.
         */
    static std::regex mathExpression;

    static std::regex pair;

    // The varibale "reg" means register, BUT word register is a keyword in c++, so I can't to use it
    static std::regex reg;

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

    unsigned int code = 0;
    bool isEmpty = true;
public:
    Operand(const std::string& operand, CommandSet::OperandType type);

    static bool isPair(const std::string& str);
    static bool isRegister(const std::string& str);
    static bool isLabel(const std::string& str);
    static bool isMathExpression(const std::string& str);

    unsigned int condition2code(const std::string& condition);
    unsigned int address2code(const std::string& address);
    unsigned int data2code(const std::string& data);
    unsigned int pair2code(const std::string& pair);
    unsigned int register2code(const std::string& reg);

    bool getIsEmpty() const;
    unsigned int getCode() const;
};


#endif // OPERAND_H
