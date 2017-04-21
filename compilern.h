#ifndef COMPILERN_H
#define COMPILERN_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "Compiler/line.h"
#include "Compiler/compilererror.h"
#include "Exceptions/compilerexception.h"
#include "Exceptions/logexceptions.h"

class CompilerN
{
private:
    std::vector<std::string> lines;
    std::vector<std::shared_ptr<CompilerError>> errors;

public:
    CompilerN();

    void compile(const std::string& inputFilename);
    std::vector<unsigned int> getObjectCode();
    void saveObjectCode(const std::string& outputFile);
};

#endif // COMPILERN_H
