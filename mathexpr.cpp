#include "mathexpr.h"

MathExpr::MathExpr(const std::string &expression):expr(expression)
{
}


int MathExpr::evaluate(const std::string& infix) {
    std::string postfix = convertToPostfix(infix);

    std::vector<std::string> eq;// = convertToPostfix(infix); // after doing this function return a vector


    if (eq.size() == 1 && isNumber(eq[0])) {
        return stoi(eq[0]);
    }

    if (eq.size() < 3 || !isOperation(eq[eq.size() - 1]) || (!isNumber(eq[0]) && !isNumber(eq[1]))) {
        throw "Wrong postfix notation";
    }

    std::stack<std::string> strStack;

    for (const std::string& s : eq) {
        if (isNumber(s)) {
            strStack.push(s);
        }

        if (isOperation(s)) {
            if (strStack.size() < 2) {
                throw "Wrong postfix equation";
            }

            int op2 = std::stoi(strStack.top());
            strStack.pop();
            int op1 = std::stoi(strStack.top());
            strStack.pop();

            /*
             * Here is not switch, because c++ can't work in switch with std::string, only with int.
             * May be to resolve this using hash.
             * TODO to do this code better, using f.e. switch
             */
            if (s.compare("+") == 0) {
                strStack.push(std::to_string(op1 + op2));
            } else if (s.compare("-") == 0) {
                strStack.push(std::to_string(op1 - op2));
            } else if (s.compare("*") == 0) {
                strStack.push(std::to_string(op1 * op2));
            } else if (s.compare("/") == 0) {
                if (op2 == 0) {
                    std::string msg = "";
                    msg.append("Dividing to zero in ").append(postfix);
                    throw msg;
                }
                strStack.push(std::to_string(op1 / op2));
            } else {
                std::string msg = "";
                msg.append("Unknown operator ").append(s).append(" in postfix equaton");
                throw msg;
            }

        }

    }
    return std::stoi(strStack.top());
}

bool MathExpr::isNumber(const std::string& s) const {
    return std::regex_match(s, std::regex("[0-9]+"));
}

bool MathExpr::isNumber(char c) const {
    return (c >= 0x30 && c <= 0x39); // ASCII: 0 is 0x30 and 9 is 0x39
}

bool MathExpr::isOperation(const std::string &s) const {
    return std::regex_match(s, std::regex("[+-[*]/]"));
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
std::string MathExpr::convertToPostfix(const std::string &infix) {

    // TODO Parse string to vector

    std::vector<std::string> eq;// = split(infix); // Maybe a function, that makes from string an array of strings

    std::string output = "";
    std::stack<std::string> strStack;

    for (unsigned int i = 0; i < eq.size(); i++) {
        std::string s = eq[i];

        if (isNumber(s)) {
            output.append(s).append(",");
        } else if (s.compare("(") == 0) {
            strStack.push(s);
        } else if (s.compare(")") == 0) {
            std::string t = strStack.top();
            strStack.pop();
            while (t.compare("(") != 0) {
                output.append(t).append(",");
                t = strStack.top();
                strStack.pop();
            }
        } else {
            while (!strStack.empty() && (operatorPriority(strStack.top()) >= operatorPriority(s))) {
                output.append(strStack.top()).append(",");
                strStack.pop();
            }
            strStack.push(s);
        }
    }

    while (!strStack.empty()) {
        output.append(strStack.top()).append(",");
        strStack.pop();
    }

    // TODO make return a vector, not as a string. it will simplify an evaluate method
    return output;
}

int MathExpr::operatorPriority(const std::string &op) const {
    if (op.compare("*") == 0 || op.compare("/") == 0) {
        return 3; // Higher priority
    } else if (op.compare("+") == 0 || op.compare("-") == 0) {
        return 2;
    } else if (op.compare("(") == 0) {
        return 1; // Less priority
    }

    return 0;
}

// split an equation to vector. f.e. 2+3 - 1* 4/3 => to vector with elements {2,+,3,-,1,*,4,/,3}
std::vector<std::string> MathExpr::equationToVector(const std::string &equation) {
    // TODO MathExpr::equationToVector

    std::vector<std::string> result;

    std::stack<std::string> strStack;

    for (std::string::const_iterator it = equation.begin(); it != equation.end(); ++it) {
        if (isNumber(*it) &&
                !strStack.empty() &&
                isNumber(strStack.top())) {
            std::string &last = strStack.top();
            last.append(std::string(1, *it));
        } else if (*it != ' ') {
            strStack.push(std::string(1, *it));
        }


//        if (isNumber(*it)) {

//            if (strStack.empty()) {
//                strStack.push(*it);
//            } else {
//                std::string &last = strStack.top();
//                if (isNumber(last)) {
//                    last.append(*it);
//                } else {
//                    strStack.push(*it);
//                }
//            }

//        } else if (it->compare(" ") != 0) {
//            strStack.push(*it);
//        }
    }

    return result;
}
