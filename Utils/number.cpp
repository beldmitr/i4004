#include "number.h"

bool Utils::Number::isBin(const std::string& str)
{
    std::regex rBin("([01]+B)|([01]+b)|(0b[01]+)|(0B[01]+)");
    return regex_match(str, rBin);
}

bool Utils::Number::isDec(const std::string& str)
{
    std::regex rDec("[0-9]+");
    return regex_match(str, rDec);
}

bool Utils::Number::isHex(const std::string& str)
{
    std::regex rHex("([0-F]+H)|([0-f]+H)|([0-F]+h)|([0-f]+h)|(0x[0-f]+)|(0X[0-f]+)|(0x[0-F]+)|(0X[0-F]+)");
    return regex_match(str, rHex);
}

bool Utils::Number::isNumber(const std::string& str)
{
    return isBin(str) || isDec(str) || isHex(str);
}
