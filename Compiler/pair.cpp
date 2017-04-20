#include "pair.h"

std::regex Pair::pairPrefix = std::regex("[Pp][0-7]");
std::regex Pair::pairPostfix = std::regex("[0-7][Pp]");

bool Pair::isPair(const std::string& str)
{
    return regex_match(str, pairPrefix) || regex_match(str, pairPostfix);
}

unsigned int Pair::getUInt(const std::string& str)
{
    if (!str.empty())
    {
        if (regex_match(str, pairPrefix))
        {
            unsigned int result = stoi(str.substr(1, str.size()));
            if (result < countPairs)
            {
                return result;
            }
        }
        else if (regex_match(str, pairPostfix))
        {
            unsigned int result = stoi(str.substr(0, str.size() - 1));
            if (result < countPairs)
            {
                return result;
            }
        }
    }

    std::string msg;
    if (str.empty())
    {
        msg = "Program expects a pair";
    }
    else
    {
        msg = "Pair " + str + " is wrong";
    }
    throw CompilerException("Pair", msg);;
}
