#include <QApplication>
#include "mainwindow.h"


int main (int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow parent;
    parent.show();

    return app.exec();
}
