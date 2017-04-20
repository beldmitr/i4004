#include "compilerexception.h"

CompilerException::CompilerException(const std::string& who,
                                     const std::string& what) : std::runtime_error(message)
{
    parent = who;
    message = what;
}

const char* CompilerException::what() const noexcept
{
    return message.c_str();
}

const char* CompilerException::who() const noexcept
{
    return parent.c_str();
}
