#ifndef COMPILER_H
#define COMPILER_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>

#include <string>
#include <vector>
#include <fstream>
#include <memory>

#include "Compiler/line.h"
#include "Compiler/firstpassline.h"
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

    static const std::regex labelRegex; // Template for Label
    static const std::regex commandRegex; // Template for instruction, it is not exect
    static const std::regex paramsRegex; // Template for operands, for both - left and right
    static const std::regex commentRegex; // Template for comments
    static const std::regex pseudoRegex; // Template for pseudo instruction =

signals:
    void onCompiled();

};

#endif // COMPILER_H
