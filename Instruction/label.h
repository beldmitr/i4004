#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "utils.h"

namespace Instruction
{
    class Label
    {
    private:
        std::string name;
        unsigned int value;

    public:
        Label(const std::string& name, unsigned int value); // In this case, value might be an address
        Label(const std::string& name, const std::string& param);
        std::string getName() const;
        unsigned int getValue() const;
    };
}

#endif // LABEL_H
