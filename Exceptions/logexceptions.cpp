#include "logexceptions.h"

LogExceptions::LogExceptions(const std::string& who,
                             const std::string& what) : std::runtime_error(what)
{
    parent = who;
    message = what;
}

const char* LogExceptions::what() const noexcept
{
    return message.c_str();
}

const char* LogExceptions::who() const noexcept
{
    return parent.c_str();
}
