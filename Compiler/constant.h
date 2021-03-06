#ifndef CONSTANT_H
#define CONSTANT_H

#include <map>
#include <string>
#include <regex>
#include <iostream>

#include "Exceptions/compilerexception.h"

class Constant
{
private:
    /*
     * It checks constant in operand, do not be confused with regex label in Label class,
     * which check or find a label in line. They are different:
     *
     * in line a label is with a comma, f.e.
     *      ABC, 45
     *      LABEL, FIM P1, 0x0
     * BUT
     * in an operand it is without comma, f.e.
     *      FIM P2, ABC+2
     *
     */
    static std::regex constant;

    static std::map<std::string, unsigned int> table;

public:
    static void add(const std::string name, unsigned int value);
    static unsigned int getByName(const std::string& name);
    static std::string getByAddr(unsigned addr);
    static void clear();
    static bool isConstantExist(const std::string& name);
    static bool isConstant(const std::string& str);
};


#endif // CONSTANT_H
