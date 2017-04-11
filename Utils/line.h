#ifndef LINE_H
#define LINE_H

#include <regex>

namespace Utils {
    namespace Assembler
    {
        class Line
        {
        private:
            static std::regex label; // Template for Label
            static std::regex instruction; // Template for instruction, it is not exect
            static std::regex operand; // Template for operands, for both - left and right
            static std::regex comment; // Template for comments

        public:
            static bool isLabel(const std::string& str);
            static bool isInstruction(const std::string& str);
            static bool isOperand(const std::string& str);
            static bool isComment(const std::string& str);

            static bool searchLabel(const std::string& line, std::smatch& matchList);
            static bool searchInstruction(const std::string& line, std::smatch& matchList);
            static bool searchOperand(const std::string& line, std::smatch& matchList);
            static bool searchComment(const std::string& line, std::smatch& matchList);

        };
    }
}


#endif // LINE_H
