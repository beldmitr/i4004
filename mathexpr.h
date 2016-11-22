#ifndef MATHEXPR_H
#define MATHEXPR_H

#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <regex>

// TODO Test this class
class MathExpr
{
private:
    std::string expr;

    // TODO make functions return const as possible
    bool isNumber(const std::string &s) const;
    bool isNumber(char c) const;
    bool isOperation(const std::string &s) const;
    int operatorPriority(const std::string &op) const;
    std::string convertToPostfix(const std::string &infix);


public:
    MathExpr(const std::string &expression);
    int evaluate(const std::string &infix); // TODO static
    std::vector<std::string> equationToVector(const std::string &equation); // TODO static
};

#endif // MATHEXPR_H
