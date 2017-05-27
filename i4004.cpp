#include "i4004.h"

I4004::I4004(int argc, char *argv[])
{
    // Create Compiler
    compiler = std::shared_ptr<Compiler>(new Compiler);

    // Create Simulator
    simulator = std::shared_ptr<Simulator>(new Simulator);

    // Create GUI
    app = std::shared_ptr<QApplication>(new QApplication(argc, argv));

    parent = std::shared_ptr<MainWindow>(new MainWindow);
    parent->show();
}

I4004::exec()
{
    return app->exec();
}
