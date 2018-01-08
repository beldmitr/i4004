#include "mathexpr.h"

/*
 * Old regex causes some bugs.
 * F.e.
 *  DONE,
 *       JUN DONE       . endless loop as end of program
 *
 * In this case regex_match returns result too slow, very slow, minutes...
 */
std::regex MathExpr::mathExpression = std::regex("(\\w?\\s?[(]*[)]*[+-]?\\s?[*]?)+");

bool MathExpr::isMathExpression(const std::string& str)
{
    return !Pair::isPair(str) && !Register::isRegister(str) && !Constant::isConstant(str) && regex_match(str, mathExpression);
}


int MathExpr::evaluate(std::string infix)
{
    // CHECK SOME ERRORS
    SearchResult error;
    // check if is not expected an operation
    error = String::search(infix, std::regex("[[:alnum:]]+[[:blank:]]+[[:alnum:]]+"));
    if (!error.isEmpty())
    {
        std::string msg = "Expected operation + or - in \"" + error.find + "\" in expression " + infix;
        throw CompilerException("MathExpr", msg);
    }
    // check if is there aren't an empty parenthesis
    error = String::search(infix, std::regex("[(][[:blank:]]*[)]"));
    if (!error.isEmpty())
    {
        std::string msg = "Empty parenthesis found in expression " + infix;
        throw CompilerException("MathExpr", msg);
    }
    // check if is there aren't two operations sequently one by one, f.e 9 ++ 1 or 9 -- 1
    error = String::search(infix, std::regex("[-+][[:blank:]]*[-+]"));
    if (!error.isEmpty())
    {
        std::string msg = "Too much operations in expression " + infix + ". A value is expected";
        throw CompilerException("MathExpr", msg);
    }


    // PREPARE an infix line
    // delete white spaces
    infix = String::trim(infix);
    // replace hex and bin numbers with dec
    infix = Number::replaceNumbersWithDec(infix);

    // EVALUATING
    std::vector<std::string> eq = infixToPostfix(infix);

    if (eq.size() == 1 && Number::isDec(eq[0]))
    {
        return Number::getUInt(eq[0]);
    }

    if (eq.size() == 1 && isConstant(eq[0]))
    {
        return Constant::getByName(eq[0]);
    }

    if (eq.size() == 2 && Number::isNumber(eq[0]) && isOperation(eq[1]))
    {
        if (eq[1] == "-")
        {
            return (0 - Number::getUInt(eq[0]));
        }
        else if (eq[1] == "+")
        {
            return Number::getUInt(eq[0]);
        }
        else
        {
            std::string msg = "Wrong expression " + infix;
            throw CompilerException("MathExpr", msg);
        }

    }

    if (eq[eq.size() - 1] == "(")
    {
        throw CompilerException("MathExpr",
                                "Wrong mathematical expression, a closing parenthesis \")\" is missing in line "
                                + infix);
    }

    if (eq.size() < 3
            || !isOperation(eq[eq.size() - 1])
            || (!Number::isDec(eq[0]) && !Number::isDec(eq[1]) && !isConstant(eq[0]) && !isConstant(eq[1])))
    {
        throw CompilerException("MathExpr", "Wrong mathematical expression " + infix);
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
                if (s.compare("-") == 0)
                {
                    std::string previous = strStack.top();
                    strStack.pop();
                    strStack.push("-"+previous);
                    strStack.push("0");
                }
                else if (s.compare("+") == 0)
                {
                    std::string previous = strStack.top();
                    strStack.pop();
                    strStack.push(previous);
                    strStack.push("0");
                }
                else
                {
                    std::string msg = "Wrong operation " + s + " in line " + infix;
                    throw CompilerException("MathExpr", msg);
                }
            }

            int op2 = std::stoi(strStack.top());
            strStack.pop();
            int op1 = std::stoi(strStack.top());
            strStack.pop();

            if (s.compare("+") == 0)
            {
                strStack.push(std::to_string(op1 + op2));
            }
            else if (s.compare("-") == 0)
            {
                strStack.push(std::to_string(op1 - op2));
            }
            else
            {
                std::string msg = "Unknown operator " + s + " in line " + infix;
                throw CompilerException("MathExpr", msg);
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
    return ((s.compare("(") == 0) || (s.compare(")") == 0));
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
            std::string t;
            if (strStack.empty())
            {
                std::string msg = "Wrong parenthesis in line " + infix;
                throw CompilerException("MathExpr", msg);
            }
            t = strStack.top();
            strStack.pop();
            while (t.compare("(") != 0)
            {
                result.push_back(t);
                if (strStack.empty())
                {
                    std::string msg = "Wrong parenthesis in line " + infix;
                    throw CompilerException("MathExpr", msg);
                }
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
            result.push_back(std::to_string(ObjectCode::getProgramCounter()));
        }
        else if (*it == ' ' || *it == '\t' )
        {
            // in other case ignore this white symbol
        }
        else
        {
            std::string msg = "Wrong symbol \"" + std::string(1, *it) + "\" in line " + infix;
            throw CompilerException("MathExpr", msg);
        }
    }

    return result;
}
