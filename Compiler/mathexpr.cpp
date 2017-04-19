#include "mathexpr.h"

//std::regex MathExpr::mathExpression = std::regex("([+-]?[[:alnum:]]+)+");
std::regex MathExpr::mathExpression = std::regex("([*]?[+-]?[[:alnum:]]+)+");

/// TODO test class and delete commented code

bool MathExpr::isMathExpression(const std::string& str)
{
    return regex_match(str, mathExpression) && !Pair::isPair(str) && !Register::isRegister(str) && !Constant::isLabel(str);
}


int MathExpr::evaluate(const std::string& infix)
{
    std::vector<std::string> eq = infixToPostfix(infix);

    if (eq.size() == 1 && Number::isDec(eq[0]))
    {
        return Number::getUInt(eq[0]);
    }

    if (eq.size() == 1 && isConstant(eq[0]))
    {
        return Constant::getByName(eq[0]);
    }

    if (eq.size() < 3
            || !isOperation(eq[eq.size() - 1])
            || (!Number::isDec(eq[0]) && !Number::isDec(eq[1]) && !isConstant(eq[0]) && !isConstant(eq[1])))
    {
        throw "Wrong postfix notation";
    }

    std::stack<std::string> strStack;

    for (const std::string& s : eq)
    {
        if (Number::isDec(s))
        {
            strStack.push(s);
        }

        if (isConstant(s))
        {
           strStack.push(std::to_string(Constant::getByName(s)));
        }

        if (isOperation(s))
        {
            if (strStack.size() < 2)
            {
                throw "Wrong postfix equation";
            }

            int op2 = std::stoi(strStack.top());
            strStack.pop();
            int op1 = std::stoi(strStack.top());
            strStack.pop();

            /*
             * Here is not switch, because c++ can't work in switch with std::string, only with int.
             * Maybe to resolve this using hash.
             * TODO Maybe to do this code better, using f.e. switch
             */
            if (s.compare("+") == 0)
            {
                strStack.push(std::to_string(op1 + op2));
            }
            else if (s.compare("-") == 0)
            {
                strStack.push(std::to_string(op1 - op2));
            }
            else if (s.compare("*") == 0)
            {
                strStack.push(std::to_string(op1 * op2));
            }
            else if (s.compare("/") == 0)
            {
                if (op2 == 0)
                {
                    std::string msg = "";
                    msg.append("Dividing to zero in ").append(infix);
                    throw msg;
                }
                strStack.push(std::to_string(op1 / op2));
            }
            else
            {
                std::string msg = "";
                msg.append("Unknown operator ").append(s).append(" in infix equaton");
                throw msg;
            }
        }
    }

    return std::stoi(strStack.top());
}

bool MathExpr::isConstant(const std::string& s)
{
    return std::regex_match(s, std::regex("[_]*[A-Z|a-z][_|0-9|A-Z|a-z]*"));
}

bool MathExpr::isOperation(const std::string &s)
{
    return ((s.compare("+") == 0) || (s.compare("-") == 0));
}

bool MathExpr::isParenthesis(const std::string &s)
{
    return ((s.compare("(") == 0)
            || (s.compare(")") == 0));
}

/*
 * Convert from infix equation to postfix
 * I think, that postfix notation is more simple to evaluate than infix
 *
 * Shunting-yard algorithm
 * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 *
 * Algorithm is the next:
 * 1. Create an empty stack called stack for keeping operators.
 *    Create an empty list for output.
 *
 * 2. Convert the input infix string to a list by using the string method split.
 *
 * 3. Scan the token list from left to right.
 * 		- If the token is an operand, append it to the end of the output list.
 *
 * 		- If the token is a left parenthesis, push it on the stack.
 *
 * 		- If the token is a right parenthesis,
 * 		  pop the stack until the corresponding left parenthesis is removed.
 * 		  Append each operator to the end of the output list.
 *
 * 		- If the token is an operator, *, /, +, or -, push it on the stack.
 * 		  However, first remove any operators already on the stack
 * 		  that have higher or equal precedence and append them to the output list.
 *
 * 4. When the input expression has been completely processed, check the stack.
 *    Any operators still on the stack can be removed and appended to the end of the output list.
 */
std::vector<std::string> MathExpr::infixToPostfix(const std::string &infix)
{
    std::vector<std::string> eq = equationToVector(infix);
    std::vector<std::string> result;

    std::stack<std::string> strStack;

    for (unsigned int i = 0; i < eq.size(); i++)
    {
        std::string s = eq[i];

        if (Number::isDec(s) || isConstant(s))
        {
            result.push_back(s);
        }
        else if (s.compare("(") == 0)
        {
            strStack.push(s);
        }
        else if (s.compare(")") == 0)
        {
            std::string t = strStack.top();
            strStack.pop();
            while (t.compare("(") != 0)
            {
                result.push_back(t);
                t = strStack.top();
                strStack.pop();
            }
        }
        else
        {
            while (!strStack.empty() && (operatorPriority(strStack.top()) >= operatorPriority(s)))
            {
                result.push_back(strStack.top());
                strStack.pop();
            }
            strStack.push(s);
        }
    }

    while (!strStack.empty())
    {
        result.push_back(strStack.top());
        strStack.pop();
    }

    return result;
}

int MathExpr::operatorPriority(const std::string &op)
{
    if (op.compare("+") == 0 || op.compare("-") == 0)
    {
        return 2;
    }
    else if (op.compare("(") == 0)
    {
        return 1; // Less priority
    }

    return 0;
}

// split an equation to vector. f.e. 2+3 - 1* 4/3 => to vector with elements {2,+,3,-,1,*,4,/,3}
std::vector<std::string> MathExpr::equationToVector(const std::string &infix)
{
    std::vector<std::string> result;

    for (std::string::const_iterator it = infix.begin(); it != infix.end(); ++it)
    {
        if ((Number::isDec(std::string(1, *it)) || isConstant(std::string(1, *it)))
                && !result.empty()
                && (Number::isDec(result.back()) || isConstant(result.back())))
        {
            std::string &last = result.back();
            last.append(std::string(1, *it));

        }
        else if (Number::isDec(std::string(1, *it))
                 || isConstant(std::string(1, *it))
                 || isParenthesis(std::string(1, *it))
                 || isOperation(std::string(1, *it)))
        {
            result.push_back(std::string(1, *it));
        }
        else if (*it == '*') // this is needed for actual address, f.e. *-5 means actual address minus 5 bytes
        {
            result.push_back(std::to_string(Address::getActual()));
        }
        else if (*it == ' ' || *it == '\t' )
        {
            // ignore if it is a white symbol
        }
        else
        {
            std::string msg = "";
            msg.append("Wrong symbol \'").append(std::string(1, *it)).append("\' in equation ").append(infix);
            /*
             * NOTE
             * The following throw statement throws an exception type "const std::string&",
             * so to catch it DO NOT use catch(const char *), but USE:
             * try { ... } catch (const std::string& e) { ... }
             */
            throw msg;
        }
    }

    return result;
}