#include <QApplication>
#include "GUI/mainwindow.h"

#include <iostream>
#include "Compiler/line.h"
#include "Compiler/constant.h"
#include <regex>

#include <map>

int main (int argc, char* argv[])
{
//    QApplication app(argc, argv);

//    MainWindow parent;
//    parent.show();

//    return app.exec();

    try
    {
//        std::vector<CommandSet::OperandStruct> s = CommandSet::getOperands("JCN");

//        for (CommandSet::OperandStruct o : s)
//        {
//            std::cout << o.toString() << std::endl;
//        }


//        std::string s = "    fgfgd  asd   asdasd    rrrrr       ";
//        String::trimBeginEnd(s);
//        std::cout << Pair::getUInt("7p") << std::endl;
        new Line("AAA, 4");
        new Line("BBB, 5");
        new Line("CCC, BBB");


//        Line* l = new Line("ddd, ISZ R2,06	 // asda dd");
//        std::cout << std::hex << l->getCode() << std::endl;
        Line* l = new Line("Icc, FIM P3, -5"); ///BUG fix this bug
                std::cout << std::hex << l->getCode() << std::endl;

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
