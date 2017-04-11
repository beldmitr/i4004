#ifndef MATHEXPR_H
#define MATHEXPR_H

#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <regex>
#include <map>

namespace Utils
{
    class MathExpr
    {
    private:

        static bool isConstant(const std::string &s);
        static bool isNumber(const std::string &s);
        static bool isParenthesis(const std::string &s);
        static bool isOperation(const std::string &s);
        static int operatorPriority(const std::string &op);
        static std::vector<std::string> infixToPostfix(const std::string &infix);
        static std::vector<std::string> equationToVector(const std::string &infix);
        static int getNumberByConst(const std::string& key, std::map<std::string, int>& tableConstants);

    public:
        static int evaluate(const std::string &infix);
        static int evaluateWithConstants(const std::string &infix, std::map<std::string, int>& tableConstants);

    };
}
#endif // MATHEXPR_H
