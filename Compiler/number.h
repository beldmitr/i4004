#ifndef NUMBER_H
#define NUMBER_H

#include <regex>

#include "Utils/string.h"

#include "Exceptions/compilerexception.h"

class Number
{
private:
    static std::regex binPrefix;    // finds 0b00000 or 0B00000 numbers
    static std::regex binPostfix;   // finds 00000b or 00000B numbers

    static std::regex dec;

    static std::regex hexPrefix;    // finds 0x00000 or 0X00000 numbers
    static std::regex hexPostfix;   // finds 00000h or 00000H numbers

public:
    static bool isBin(const std::string& str);
    static bool isDec(const std::string& str);
    static bool isHex(const std::string& str);
    static bool isNumber(const std::string& str);
    static unsigned int getUInt(const std::string& str);

    static std::string replaceNumbersWithDec(const std::string& str);
};


#endif // NUMBER_H
