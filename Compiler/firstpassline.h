#ifndef FIRSTPASSLINE_H
#define FIRSTPASSLINE_H

#include <string>

#include "Compiler/compiler.h"
#include "Utils/string.h"
#include "Utils/searchresult.h"

class FirstPassLine
{
public:
    explicit FirstPassLine(std::string line);
    virtual ~FirstPassLine();

};

#endif // FIRSTPASSLINE_H
