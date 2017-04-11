#ifndef OPERAND_H
#define OPERAND_H

#include <regex>
#include <string>

#include "utils.h"
#include "Instruction/labeltable.h"

namespace Instruction
{
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
        Operand(const std::string& operand);

        static bool isPair(const std::string& str);
        static bool isRegister(const std::string& str);
        static bool isLabel(const std::string& str);
        static bool isMathExpression(const std::string& str);

        static bool searchPair(const std::string& str, std::smatch& matchList);
        static bool searchRegister(const std::string& str, std::smatch& matchList);
        static bool searchLabel(const std::string& str, std::smatch& matchList);
        static bool searchMathExpression(const std::string& str, std::smatch& matchList);

        bool getIsEmpty() const;
        unsigned int getCode() const;
    };
}

#endif // OPERAND_H
