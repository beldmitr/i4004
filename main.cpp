#include <QApplication>
#include "GUI/mainwindow.h"

#include <iostream>
#include "utils.h"
#include "Instruction/instruction.h"

int main (int argc, char* argv[])
{
//    QApplication app(argc, argv);

//    MainWindow parent;
//    parent.show();

//    return app.exec();

    try
    {
//        Instruction::Instruction instruction("FIM", "P1, 0x111");
        std::cout << Utils::Number::getUInt("1010B") << std::endl;
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
