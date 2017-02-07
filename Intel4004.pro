TEMPLATE = app
TARGET = Intel4004
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += \
    GUI/mainwindow.cpp \
    GUI/dataramwidget.cpp \
    GUI/romwidget.cpp \
    GUI/programramwidget.cpp \
    GUI/asmeditor.cpp \
    GUI/dataramwidgetn.cpp \
    GUI/subwindow.cpp \
    GUI/iowidget.cpp \
    GUI/iolistcomponents.cpp \
    GUI/memorytable.cpp \
    GUI/iopanel.cpp \
    GUI/chipdataram.cpp \
    main.cpp \
    compiler.cpp \
    error.cpp \
    simulator.cpp \
    rom.cpp \
    pram.cpp \
    dram.cpp \
    cpu.cpp \
    stack.cpp \
    dataramregister.cpp \
    dataramchip.cpp \
    datarambank.cpp \
    mathexpr.cpp \
    GUI/cpuwidget.cpp \
    GUI/led.cpp \
    GUI/button.cpp \
    GUI/iowidgetn.cpp \
    GUI/coloredcombobox.cpp

HEADERS += \
    GUI/mainwindow.h \
    GUI/dataramwidget.h \
    GUI/romwidget.h \
    GUI/programramwidget.h \
    GUI/asmeditor.h \
    GUI/dataramwidgetn.h \
    GUI/subwindow.h \
    GUI/iowidget.h \
    GUI/iolistcomponents.h \
    GUI/memorytable.h \
    GUI/chipdataram.h \
    GUI/iopanel.h \
    compiler.h \
    error.h \
    simulator.h \
    rom.h \
    pram.h \
    dram.h \
    cpu.h \
    stack.h \
    dataramregister.h \
    dataramchip.h \
    datarambank.h \
    mathexpr.h \
    Interfaces/icompiler.h \
    GUI/cpuwidget.h \
    GUI/led.h \
    GUI/button.h \
    GUI/iowidgetn.h \
    GUI/coloredcombobox.h

RESOURCES += \
    resources.qrc

