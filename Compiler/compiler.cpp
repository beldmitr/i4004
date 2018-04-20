#include "compiler.h"

const std::regex Compiler::labelRegex = std::regex("^[[:alpha:]][[:alnum:]]{2,}[,:]");
const std::regex Compiler::commandRegex = std::regex("NOP|JCN|FIM|SRC|FIN|JIN|JUN|JMS|INC|ISZ|ADD|SUB|LD|XCH|BBL|LDM|WRM|WMP|WRR|WPM|WR0|WR1|WR2|WR3|SBM|RDM|RDR|ADM|RD0|RD1|RD2|RD3|CLB|CLC|IAC|CMC|CMA|RAL|RAR|TCC|DAC|TCS|STC|DAA|KBP|DCL");
const std::regex Compiler::paramsRegex = std::regex("([[:blank:]]+[[:print:]]+[[:blank:]]*)(,)?([[:blank:]]*[[:print:]]+[[:blank:]]*)?");
const std::regex Compiler::commentRegex = std::regex("[/;][[:print:]]*");
const std::regex Compiler::pseudoRegex = std::regex("[[:blank:]]*=[[:blank:]]+");

std::vector<std::shared_ptr<CompilerError> > Compiler::getErrors() const
{
    return errors;
}

Compiler::Compiler() : QObject()
{
    // is empty
}

Compiler::~Compiler()
{

}

void Compiler::compile(const std::string& inputFilename)
{
    if (inputFilename.empty())
    {
        // Just nothing for compiling

        emit onCompiledError();
        return;
    }

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
        std::string msg = "File " + inputFilename + " can't be open for reading.";
        std::cerr << msg << std::endl;
        throw LogExceptions("Compiler", msg);
    }

    // delete old code
    ObjectCode::reset();

    // delete old constant table
    Constant::clear();

    // delete old error messages
    errors.clear();

    // First passing
    // Counting labels
    unsigned row = 1;

    for (const std::string& l : lines)
    {
        try
        {
            std::shared_ptr<FirstPassLine>(new FirstPassLine(l));
        }
        catch(const CompilerException& ex)
        {
            /*
             * Here is a dilemma. If I left this block empty, then some errors in label won't be shown.
             * But if I will show these errors, some of them will be repeated in the second pass.
             * For best solution I need to make several types of CompilerExceptions, f.e. special
             * exceptions for labels or for first pass, which will be shown here.
             */

            errors.push_back(std::shared_ptr<CompilerError>(new CompilerError(row, ex.what())));

            std::cerr << "Line " << row << ": Error " << ex.what() << std::endl;
            std::cerr << "\tFrom " << ex.who() << std::endl;
        }
        row++;
    }


    ObjectCode::setProgramCounter(0);

    // Second passing
    // Parse lines
    row = 1;

    for (const std::string& l : lines)
    {
        try
        {
            std::shared_ptr<Line>(new Line(l));
        }
        catch(const CompilerException& ex)
        {
            errors.push_back(std::shared_ptr<CompilerError>(new CompilerError(row, ex.what())));

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
        std::string msg = "File " + outputFile + " can't be open for writing.";
        std::cerr << msg << std::endl;
        throw LogExceptions("Compiler", msg);
    }
}
