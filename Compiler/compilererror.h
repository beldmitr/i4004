#ifndef COMPILERERROR_H
#define COMPILERERROR_H

#include <string>

class CompilerError
{
public:
    const unsigned int row = 0;
    const std::string message = "";

public:
    CompilerError(unsigned int row, const std::string& message);

};

#endif // COMPILERERROR_H
