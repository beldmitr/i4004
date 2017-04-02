TEMPLATE = app
TARGET = Intel4004
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += \
    GUI/mainwindow.cpp \
    GUI/romwidget.cpp \
    GUI/programramwidget.cpp \
    GUI/asmeditor.cpp \
    GUI/dataramwidgetn.cpp \
    GUI/subwindow.cpp \
    GUI/memorytable.cpp \
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
    GUI/coloredcombobox.cpp \
    GUI/chooseiowidget.cpp \
    GUI/sevensegmentio.cpp \
    GUI/sevensegmentpanel.cpp \
    GUI/buttonpanel.cpp \
    GUI/editor.cpp \
    GUI/highlighter.cpp \
    GUI/ledpanel.cpp \
    GUI/editorsubwindow.cpp \
    GUI/ledsubwindow.cpp \
    GUI/sevensegmentsubwindow.cpp

HEADERS += \
    GUI/mainwindow.h \
    GUI/romwidget.h \
    GUI/programramwidget.h \
    GUI/asmeditor.h \
    GUI/dataramwidgetn.h \
    GUI/subwindow.h \
    GUI/memorytable.h \
    GUI/chipdataram.h \
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
    GUI/coloredcombobox.h \
    GUI/chooseiowidget.h \
    GUI/sevensegmentio.h \
    GUI/sevensegmentpanel.h \
    GUI/buttonpanel.h \
    GUI/editor.h \
    GUI/highlighter.h \
    GUI/ledpanel.h \
    GUI/editorsubwindow.h \
    GUI/ledsubwindow.h \
    GUI/sevensegmentsubwindow.h

RESOURCES += \
    resources.qrc

