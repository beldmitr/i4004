#ifndef CONSTANT_H
#define CONSTANT_H

#include <map>
#include <string>

class Constant
{
private:
    static std::map<std::string, unsigned int> table;

public:
    static void add(const std::string name, unsigned int value);
    static unsigned int getByName(const std::string& name);
    static void clear();
    static bool isLabelExist(const std::string& name);
};


#endif // CONSTANT_H
