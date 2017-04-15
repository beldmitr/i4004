#ifndef LABELTABLE_H
#define LABELTABLE_H

#include <map>
#include <string>

#include "Compiler/label.h"

class Label;

class LabelTable
{
private:
    static std::map<std::string, unsigned int> table;

public:
    static void add(const Label& label);
    static unsigned int getByName(const std::string& name);
    static void clear();
    static bool isLabelExist(const std::string& name);
};


#endif // LABELTABLE_H
