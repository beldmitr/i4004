#include <QApplication>
#include "GUI/mainwindow.h"

#include <iostream>
#include "Compiler/line.h"
#include "Compiler/constant.h"
#include <regex>

#include <map>

#include "Compiler/compiler.h"

int main (int argc, char* argv[])
{
    //    QApplication app(argc, argv);

    //    MainWindow parent;
    //    parent.show();

    //    return app.exec();

    Compiler* c = new Compiler;
    c->compile("D:/a.asm");
    c->saveObjectCode("D:/a.bin");

    int a = 9 + + 1;

    return 0;
}
