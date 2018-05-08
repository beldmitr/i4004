#include <QApplication>
#include <QObject>
#include <QThread>

#include <memory>
#include <vector>

#include "Compiler/compiler.h"
#include "Simulator/simulator.h"
#include "GUI/mainwindow.h"

#include "Exceptions/compilerexception.h"
#include "Exceptions/logexceptions.h"

int main (int argc, char* argv[])
{
    std::shared_ptr<Compiler> compiler;
    std::shared_ptr<Simulator> simulator;
    std::shared_ptr<QApplication> app;
    std::shared_ptr<MainWindow> parent;

    try
    {
        // Create Compiler
        compiler = std::shared_ptr<Compiler>(new Compiler);

        // Create Simulator
        simulator = std::shared_ptr<Simulator>(new Simulator(*compiler.get()));

        // Create GUI
        app = std::shared_ptr<QApplication>(new QApplication(argc, argv));
        parent = std::shared_ptr<MainWindow>(new MainWindow(*compiler.get(), *simulator.get()));
        parent->show();
    }
    catch(const CompilerException& ex)
    {
        std::cerr << "Compiler exception : " << ex.what() << " from " << ex.who() << std::endl;
    }
    catch(const LogExceptions& ex)
    {
        std::cerr << "Log exception : " << ex.what() << " from " << ex.who() << std::endl;
    }
    catch(const std::exception& ex)
    {
        std::cerr << "Exception : " << ex.what() << std::endl;
    }

    return app->exec();
}
