#ifndef LABELTABLE_H
#define LABELTABLE_H

#include <map>
#include <string>

#include "Instruction/label.h"

class Label;

namespace Instruction
{
    class LabelTable
    {
    private:
        static std::map<std::string, unsigned int> table;

    public:
        static void add(const Label& label);
        static unsigned int getByName(const std::string& name);
        static void clear();
    };
}

#endif // LABELTABLE_H
