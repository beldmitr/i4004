#ifndef COMPILEREXCEPTION_H
#define COMPILEREXCEPTION_H

#include <stdexcept>
#include <string>

class CompilerException : public std::runtime_error
{
public:
    CompilerException(const std::string& who, const std::string& message);

    // exception interface
public:
    const char* what() const noexcept;

    const char* who() const noexcept;

private:
    std::string parent;
    std::string message;
};

#endif // COMPILEREXCEPTION_H
