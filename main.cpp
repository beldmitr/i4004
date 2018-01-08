#include <QApplication>
#include <QObject>
#include <QThread>

#include <memory>
#include <vector>

#include "Compiler/compiler.h"
#include "Simulator/simulator.h"
#include "GUI/mainwindow.h"

int main (int argc, char* argv[])
{
    std::shared_ptr<Compiler> compiler;
    std::shared_ptr<Simulator> simulator;
    std::shared_ptr<QApplication> app;
    std::shared_ptr<MainWindow> parent;

    // Create Compiler
    compiler = std::shared_ptr<Compiler>(new Compiler);

    // Create Simulator
    simulator = std::shared_ptr<Simulator>(new Simulator(*compiler.get()));

    // Create GUI
    app = std::shared_ptr<QApplication>(new QApplication(argc, argv));
    parent = std::shared_ptr<MainWindow>(new MainWindow(*compiler.get(), *simulator.get()));
    parent->show();

    return app->exec();
}
