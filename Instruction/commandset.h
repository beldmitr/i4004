#ifndef COMMANDSET_H
#define COMMANDSET_H

#include <map>
#include <string>

namespace Instruction
{
    class CommandSet
    {
    private:
        static std::map<std::string, unsigned int> set;

    public:
        static bool isCommand(const std::string& command);
        static unsigned int getCommand(const std::string& command);
        static unsigned int getLength(const std::string& command);
    };
}

#endif // COMMANDSET_H
