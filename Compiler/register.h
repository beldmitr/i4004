#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include <regex>

#include "Exceptions/compilerexception.h"

class Register
{
private:
    static std::regex registerPrefix;
    static std::regex registerPostfix;

    // but it doesn't influence on a regex: registerPrefix and registerPostfix
    static const unsigned int countRegisters = 16;

public:
    static bool isRegister(const std::string& str);
    static unsigned int getUInt(const std::string& reg);
};

#endif // REGISTER_H
