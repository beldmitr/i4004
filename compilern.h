#ifndef COMPILERN_H
#define COMPILERN_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "Compiler/line.h"

class CompilerN
{
private:
    std::ifstream input;
    std::ofstream output;

    std::vector<std::string> lines;

public:
    CompilerN();

    void compile(const std::string& inputFilename);
};

#endif // COMPILERN_H
