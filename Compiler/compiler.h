#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "Compiler/line.h"
#include "Compiler/compilererror.h"
#include "Exceptions/compilerexception.h"
#include "Exceptions/logexceptions.h"

class Compiler
{
private:
    std::vector<std::string> lines;
    std::vector<std::shared_ptr<CompilerError>> errors;

public:
    Compiler();

    void compile(const std::string& inputFilename);
    std::vector<unsigned int> getObjectCode();
    void saveObjectCode(const std::string& outputFile);
};

#endif // COMPILER_H
