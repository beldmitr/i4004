#include "register.h"

std::regex Register::registerPrefix = std::regex("[Rr]([0-9]|(1[0-5]))");
std::regex Register::registerPostfix = std::regex("([0-9]|(1[0-5]))[Rr]");

bool Register::isRegister(const std::string& str)
{
    return regex_match(str, registerPrefix) || regex_match(str, registerPostfix);
}

unsigned int Register::getUInt(const std::string& str)
{
    if (!str.empty())
    {
        if (regex_match(str, registerPrefix))
        {
            unsigned int result = stoi(str.substr(1, str.size()));
            if (result < countRegisters)
            {
                return result;
            }
        }
        else if (regex_match(str, registerPostfix))
        {
            unsigned int result = stoi(str.substr(0, str.size() - 1));
            if (result < countRegisters)
            {
                return result;
            }
        }
    }

    std::string msg;
    if (str.empty())
    {
        msg = "Register::Program expects a register";
    }
    else
    {
        msg = "Register::Register " + str + " is wrong";
    }
    throw msg;
}
