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
        std::string msg = "Compiler::File " + inputFilename + " can't be open.";
        throw msg;
    }

    // parse lines
    for (const std::string& l : lines)
    {
        try
        {
            std::shared_ptr<Line>(new Line(l));
        }
        catch(const std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
        }
//        catch(const std::string& ex)
//        {
//            std::cerr << ex << std::endl;
//        }
//        catch(const char* ex)
//        {
//            std::cerr << ex << std::endl;
//        }


    }

}
