#include <QApplication>
#include "GUI/mainwindow.h"

#include <iostream>
#include "Compiler/line.h"
#include "Compiler/constant.h"
#include <regex>

#include <map>

#include "compilern.h"

int main (int argc, char* argv[])
{
//    QApplication app(argc, argv);

//    MainWindow parent;
//    parent.show();

//    return app.exec();

    try
    {
        CompilerN* c = new CompilerN;
        c->compile("D:/a.asm");
        std::map<unsigned int, unsigned int> m = ObjectCode::getTable();

        Line l("= 256");
//        std::cout << std::hex << l.getInstruction()->getCode() << std::endl;
    }
    catch(std::string ex)
    {
        std::cout << ex << std::endl;
    }
    catch(const char* ex)
    {
        std::cout << ex << std::endl;
    }
    catch(std::invalid_argument ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch(std::regex_error ex)
    {
        std::cout << ex.what() << std::endl;
    }


    return 0;
}
