#include "number.h"

std::regex Number::binPrefix = std::regex("(0b[01]+)|(0B[01]+)");
std::regex Number::binPostfix = std::regex("([01]+b)|([01]+B)");

std::regex Number::dec = std::regex("[0-9]+");

std::regex Number::hexPrefix = std::regex("(0x[0-f]+)|(0X[0-f]+)|(0x[0-F]+)|(0X[0-F]+)");
std::regex Number::hexPostfix = std::regex("([0-F]+H)|([0-f]+H)|([0-F]+h)|([0-f]+h)");

bool Number::isBin(const std::string& str)
{
    return regex_match(str, binPrefix) || regex_match(str, binPostfix);
}

bool Number::isDec(const std::string& str)
{
    return regex_match(str, dec);
}

bool Number::isHex(const std::string& str)
{
    return regex_match(str, hexPrefix) || regex_match(str, hexPostfix);
}

bool Number::isNumber(const std::string& str)
{
    return isBin(str) || isDec(str) || isHex(str);
}

unsigned int Number::getUInt(const std::string& str)
{
    if(regex_match(str, binPrefix))
    {
        std::string result = str.substr(2, str.size() - 2);
        return std::stoi(result, nullptr, 2);
    }
    else if (regex_match(str, binPostfix))
    {
        std::string result = str.substr(0, str.size() - 1);
        return std::stoi(result, nullptr, 2);
    }
    else if (regex_match(str, dec))
    {
        return std::stoi(str, nullptr, 10);
    }
    else if (regex_match(str, hexPrefix))
    {
        std::string result = str.substr(2, str.size()-2);
        return std::stoi(result, nullptr, 16);
    }
    else if (regex_match(str, hexPostfix))
    {
        std::string result = str.substr(0, str.size() - 1);
        return std::stoi(result, nullptr, 16);
    }
    else
    {
        std::string msg = "Number::Unknown type of a number " + str;
        throw msg;
    }
}

int Number::to4bit(int num)
{
    return (num % 0x10);
}

int Number::to8bit(int num)
{
    return (num % 0x100);
}

int Number::to12bit(int num)
{
    return (num % 0x1000);
}

int Number::to4bitStrong(int num)
{
    return (num & 0xF);
}

int Number::to8bitStrong(int num)
{
    return (num & 0xFF);
}

int Number::to12bitStrong(int num)
{
    return (num & 0xFFF);
}
