#ifndef NUMBER_H
#define NUMBER_H

#include <regex>

namespace Utils {
    class Number
    {
    public:
        bool static isBin(const std::string& str);
        bool static isDec(const std::string& str);
        bool static isHex(const std::string& str);

        bool static isNumber(const std::string& str);
    };
}

#endif // NUMBER_H
