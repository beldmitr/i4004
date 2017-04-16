#ifndef NUMBER_H
#define NUMBER_H

#include <regex>

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

    /// TODO Do I need all this stuff ????
    static int to4bit(int num);
    static int to8bit(int num);
    static int to12bit(int num);
    static int to4bitStrong(int num);
    static int to8bitStrong(int num);
    static int to12bitStrong(int num);

};


#endif // NUMBER_H
