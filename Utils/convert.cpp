#include "convert.h"

/// TODO test this class and remove commented code
int Utils::Convert::register2int(const std::string& str)
{
    std::string t = str;
    if (!t.empty() && Instruction::Operand::isRegister(str))
    {
        t.erase(0, 1);

                int n = stoi(t);
//        int n = QString::fromStdString(t).toInt(); // TODO QString to std::string

        return (n >= 0 && n <= 0xF) ? n : -1;
    }

    return -1;
}

int Utils::Convert::pair2int(const std::string& str)
{
    std::string t = str;
    if (!t.empty() && Instruction::Operand::isPair(str))
    {
        t.erase(0, 1);

                int n = stoi(t);
//        int n = QString::fromStdString(t).toInt(); // TODO QString to std::string

        return (n >= 0 && n <= 7) ? n : -1;
    }

    return -1;
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
