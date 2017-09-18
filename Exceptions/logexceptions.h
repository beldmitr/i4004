#ifndef LOGEXCEPTIONS_H
#define LOGEXCEPTIONS_H

#include <stdexcept>
#include <string>

class LogExceptions : public std::runtime_error
{
public:
    LogExceptions(const std::string& who, const std::string& what);

    // exception interface
public:
    const char* what() const noexcept;

    const char* who() const noexcept;

private:
    std::string parent;
    std::string message;
};

#endif // LOGEXCEPTIONS_H
