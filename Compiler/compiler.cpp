#include "compiler.h"

std::vector<std::shared_ptr<CompilerError> > Compiler::getErrors() const
{
    return errors;
}

Compiler::Compiler() : QObject()
{
    // is empty
}

void Compiler::compile(const std::string& inputFilename)
{
    // delete old source code
    lines.clear();

    // open and read source file
    std::ifstream input(inputFilename.c_str(), std::ios::in);

    if (input.is_open())
    {
        std::string line;

        while (getline(input, line))
        {
            lines.push_back(line);
        }

        input.close();
    }
    else
    {
        std::string msg = "File " + inputFilename + " can't be open.";
        throw LogExceptions("Compiler", msg);
    }

    // delete old code
    ObjectCode::reset();

    // delete old constant table
    Constant::clear();

    // delete old error messages
    errors.clear();

    // parse lines
    unsigned int row = 1;
    for (const std::string& l : lines)
    {
        try
        {
            std::shared_ptr<Line>(new Line(l));
        }
        catch(const CompilerException& ex)
        {
            errors.push_back(std::shared_ptr<CompilerError>(new CompilerError(row, ex.what())));

            /// TODO delete this std::cerr
            std::cerr << "Line " << row << ": Error " << ex.what() << std::endl;
            std::cerr << "\tFrom " << ex.who() << std::endl;
        }
        row++;
    }

    emit onCompiled();
}

std::vector<unsigned int> Compiler::getObjectCode()
{
    return ObjectCode::getTable();
}

void Compiler::saveObjectCode(const std::string& outputFile)
{
    std::ofstream output(outputFile.c_str(), std::ios::out | std::ios::binary);

    if (output.is_open())
    {
        for (unsigned int p : getObjectCode())
        {
            output.write(reinterpret_cast<const char*>(&p), 1);
        }

        output.close();
    }
    else
    {
        std::string msg = "File " + outputFile + " can't be open.";
        throw LogExceptions("Compiler", msg);
    }
}
