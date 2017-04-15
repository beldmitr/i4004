#include <QApplication>
#include "GUI/mainwindow.h"

#include <iostream>
#include "Compiler/line.h"
#include <regex>

int main (int argc, char* argv[])
{
//    QApplication app(argc, argv);

//    MainWindow parent;
//    parent.show();

//    return app.exec();

    try
    {
        Line* l = new Line("XCH R1	 // asda dd");
        std::cout << std::hex << l->getCode() << std::endl;
//        Line* l = new Line("I FIM bananas");

//        std::cout << (char)CommandSet::getOperandType("JCN", 1) << std::endl;
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


    return 0;
}
