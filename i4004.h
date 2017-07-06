#ifndef I4004_H
#define I4004_H

#include <QApplication>
#include <QObject>
#include <QThread>

#include <memory>
#include <vector>

#include "Compiler/compiler.h"
#include "Simulator/simulator.h"
#include "GUI/mainwindow.h"

class I4004 : public QObject
{
    Q_OBJECT
public:
    I4004(int argc, char* argv[]);

    exec();

private:
    std::shared_ptr<Compiler> compiler;
    std::shared_ptr<Simulator> simulator;
    std::shared_ptr<QApplication> app;
    std::shared_ptr<MainWindow> parent;
};

#endif // I4004_H
