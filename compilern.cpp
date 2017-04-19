#include "compilern.h"

CompilerN::CompilerN()
{

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
        std::string msg = "Compiler::File " + inputFilename + " can't be open.";
        throw msg;
    }

    // parse lines
    for (const std::string& l : lines)
    {
        std::shared_ptr<Line> line = std::shared_ptr<Line>(new Line(l));

        std::string commandName = line->getInstruction()->getCommand()->getName();

    }

}
