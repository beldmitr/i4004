#ifndef MATHEXPR_H
#define MATHEXPR_H

#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <regex>

class MathExpr
{
private:
    static bool isNumber(const std::string &s);
    static bool isParenthesis(const std::string &s);
    static bool isOperation(const std::string &s);
    static int operatorPriority(const std::string &op);
    static std::vector<std::string> infixToPostfix(const std::string &infix);
    static std::vector<std::string> equationToVector(const std::string &infix);

public:
    static int evaluate(const std::string &infix);

};

#endif // MATHEXPR_H
