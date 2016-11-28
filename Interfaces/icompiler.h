#ifndef ICOMPILER_H
#define ICOMPILER_H

#include<string>
#include "error.h"

class ICompiler {
public:
    virtual void toCompile() = 0;
    virtual std::vector<Error> getErrors() const = 0;
    virtual std::vector<unsigned int> getCompiledCode() const = 0;

};

#endif // ICOMPILER_H

