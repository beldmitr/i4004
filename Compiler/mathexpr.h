#ifndef MATHEXPR_H
#define MATHEXPR_H

#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <regex>

#include "Compiler/objectcode.h"
#include "Compiler/constant.h"
#include "Compiler/pair.h"
#include "Compiler/register.h"
#include "Compiler/number.h"
#include "Compiler/address.h"

    class MathExpr
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

        static bool isConstant(const std::string &s);   /// TODO use standard isConstant from Label or Constant class
        static bool isParenthesis(const std::string &s);    /// TODO I dont need parentheses

        static bool isOperation(const std::string &s);
        static int operatorPriority(const std::string &op);
        static std::vector<std::string> infixToPostfix(const std::string &infix);
        static std::vector<std::string> equationToVector(const std::string &infix);

    public:
        static int evaluate(const std::string &infix);
        static bool isMathExpression(const std::string& str);

    };

#endif // MATHEXPR_H
