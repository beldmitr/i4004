#include "compilern.h"

CompilerN::CompilerN()
{
    // is empty
}

void CompilerN::compile(const std::string& inputFilename)
{
    // open and read source file
    input.open(inputFilename.c_str(), std::ios::in);

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
        /*
         * TODO decide what to do with this exception,
         * obviously we need a LogExceptions class,
         * which will collect not runtime compile errors
         */
        std::string msg = "File " + inputFilename + " can't be open.";
        throw LogExceptions("Compiler", msg);
    }

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
            std::cerr << "Line " << row << ": Error " << ex.what() << std::endl;
            std::cerr << "\tFrom " << ex.who() << std::endl;
        }
        row++;
    }
}

std::map<unsigned int, unsigned int> CompilerN::getObjectCode()
{
    return ObjectCode::getTable();
}
