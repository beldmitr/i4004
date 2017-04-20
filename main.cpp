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

    CompilerN* c = new CompilerN;
    c->compile("D:/a.asm");


    return 0;
}
