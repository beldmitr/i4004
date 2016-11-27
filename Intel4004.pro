TEMPLATE = app
TARGET = Intel4004
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    compiler.cpp \
    dataramwidget.cpp \
    romwidget.cpp \
    memorytable.cpp \
    programramwidget.cpp \
    processorwidget.cpp \
    asmeditor.cpp \
    iopanel.cpp \
    dataramwidgetn.cpp \
    chipdataram.cpp \
    subwindow.cpp \
    error.cpp \
    instruction.cpp \
    simulator.cpp \
    rom.cpp \
    pram.cpp \
    dram.cpp \
    cpu.cpp \
    stack.cpp \
    iowidget.cpp \
    iolistcomponents.cpp \
    dataramregister.cpp \
    dataramchip.cpp \
    datarambank.cpp \
    mathexpr.cpp

HEADERS += \
    mainwindow.h \
    compiler.h \
    dataramwidget.h \
    romwidget.h \
    memorytable.h \
    programramwidget.h \
    processorwidget.h \
    asmeditor.h \
    iopanel.h \
    dataramwidgetn.h \
    chipdataram.h \
    subwindow.h \
    error.h \
    instruction.h \
    simulator.h \
    rom.h \
    pram.h \
    dram.h \
    cpu.h \
    stack.h \
    iowidget.h \
    iolistcomponents.h \
    dataramregister.h \
    dataramchip.h \
    datarambank.h \
    mathexpr.h

RESOURCES += \
    resources.qrc

