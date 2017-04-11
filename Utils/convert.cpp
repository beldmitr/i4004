#include "convert.h"

/// TODO test this class and remove commented code
/// TODO remove unused functions
unsigned int Utils::Convert::register2uint(const std::string& str)
{
    /*
     * FIXME expects only Rx or rx register, but not in reverse order
     * Add this possibility
     */
    if (!str.empty() && Instruction::Operand::isRegister(str))
    {
        unsigned int result = stoi(str.substr(1, str.size()));
        if (result < 0x10)  /// TODO magic number
        {
            return result;
        }
    }

    std::string msg = "Convert::Register " + str + " is wrong";
    throw msg;
}

unsigned int Utils::Convert::pair2uint(const std::string& str)
{
    /*
     * FIXME expects only Px or px pair, but not in reverse order
     * Add this possibility
     */
    if (!str.empty() && Instruction::Operand::isPair(str))
    {
        unsigned int result = stoi(str.substr(1, str.size()));
        if (result < 8) /// TODO 8 is a magic number.
        {
            return result;
        }
    }

    std::string msg = "Convert::Pair " + str + " is wrong";
    throw msg;
}

int Utils::Convert::condition2int(const std::string& str)
{
    if(str.empty())
    {
        return -1;
    }

        return stoi(str);
//    return QString::fromStdString(exp).toInt(); // TODO QString to std::string
}

int Utils::Convert::address2int(const std::string& str)
{
    if(str.empty())
    {
        return -1;
    }

        return stoi(str);
//    return QString::fromStdString(exp).toInt(); // TODO QString to std::string
}

int Utils::Convert::bin2int(const std::string& str)
{
    /// TODO bin2int
}

int Utils::Convert::hex2int(const std::string& str)
{
    /// TODO hex2int
}

int Utils::Convert::dec2int(const std::string& str)
{
    if (str.empty())
    {
        return -1;
    }

        return stoi(str);
//    return QString::fromStdString(exp).toInt(); // TODO QString to std::string
}

int Utils::Convert::to4bit(int num)
{
    return (num % 0x10);
}

int Utils::Convert::to8bit(int num)
{
    return (num % 0x100);
}

int Utils::Convert::to12bit(int num)
{
    return (num % 0x1000);
}

int Utils::Convert::to4bitStrong(int num)
{
    return (num & 0xF);
}

int Utils::Convert::to8bitStrong(int num)
{
    return (num & 0xFF);
}

int Utils::Convert::to12bitStrong(int num)
{
    return (num & 0xFFF);
}
