#include "compilererror.h"

CompilerError::CompilerError(unsigned int row, const std::string& message)
{
    const_cast<unsigned int&>(this->row) = row;
    const_cast<std::string&>(this->message) = message;
}

