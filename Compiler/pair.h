#ifndef PAIR_H
#define PAIR_H

#include <string>
#include <regex>

#include "Exceptions/compilerexception.h"

class Pair
{
private:
    static std::regex pairPrefix;
    static std::regex pairPostfix;

    // but it doesn't influence on a regex: pairPrefix and pairPostfix
    static const unsigned int countPairs = 8;

public:
    static unsigned int getUInt(const std::string& str);
    static bool isPair(const std::string& str);
};

#endif // PAIR_H
