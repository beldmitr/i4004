#ifndef STRING_H
#define STRING_H

#include <string>
#include <regex>
#include <vector>

namespace Utils
{
    class String
    {
    public:
        static std::string trimStrong(const std::string& str); // Delete all whitespaces from string
        static std::string trim(const std::string& str); // It will left only 1 whitespace

        // divide string by divider to vector of strings
        static std::vector<std::string> divideBy(const std::string& str, const std::string& divider);
    };
}

#endif // STRING_H
