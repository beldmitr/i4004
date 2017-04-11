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
        Instruction::Instruction instruction("FIM", "P1, 236++6");
    }
    catch(std::string ex)
    {
        std::cout << ex << std::endl;
    }

    return 0;
}
