#ifndef COMPILER_H
#define COMPILER_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "Compiler/line.h"
#include "Compiler/compilererror.h"
#include "Exceptions/compilerexception.h"
#include "Exceptions/logexceptions.h"

class Compiler : public QObject
{
    Q_OBJECT
private:
    std::vector<std::string> lines;
    std::vector<std::shared_ptr<CompilerError>> errors;

public:
    explicit Compiler();
    virtual ~Compiler();

    void compile(const std::string& inputFilename);
    std::vector<unsigned int> getObjectCode();
    void saveObjectCode(const std::string& outputFile);

    std::vector<std::shared_ptr<CompilerError> > getErrors() const;

signals:
    void onCompiled();

};

#endif // COMPILER_H
