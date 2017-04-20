#ifndef ICOMPILER_H
#define ICOMPILER_H

//#include<string>
#include "compilererror.h"

class ICompiler
{
public:
    virtual void toCompile() = 0;
    virtual std::vector<CompilerError> getErrors() const = 0;
    virtual std::vector<unsigned int> getCompiledCode() const = 0;

};

#endif // ICOMPILER_H

