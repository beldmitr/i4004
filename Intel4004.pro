TEMPLATE = app
TARGET = Intel4004
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += \
    GUI/mainwindow.cpp \
    GUI/romwidget.cpp \
    GUI/programramwidget.cpp \
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
    Compiler/mathexpr.cpp \
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
    GUI/sevensegmentsubwindow.cpp \
    GUI/buttonsubwindow.cpp \
    GUI/dataramwidget.cpp \
    Compiler/number.cpp \
    Compiler/label.cpp \
    Compiler/command.cpp \
    Compiler/commandset.cpp \
    Utils/string.cpp \
    Compiler/params.cpp \
    Compiler/operand.cpp \
    Compiler/labeltable.cpp \
    compilern.cpp \
    Compiler/instruction.cpp \
    Compiler/line.cpp \
    Utils/searchresult.cpp \
    Compiler/pair.cpp \
    Compiler/register.cpp \
    Compiler/condition.cpp \
    Compiler/address.cpp \
    Compiler/data.cpp

HEADERS += \
    GUI/mainwindow.h \
    GUI/romwidget.h \
    GUI/programramwidget.h \
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
    Compiler/mathexpr.h \
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
    GUI/sevensegmentsubwindow.h \
    GUI/buttonsubwindow.h \
    GUI/dataramwidget.h \
    Compiler/number.h \
    Compiler/label.h \
    Compiler/command.h \
    Compiler/commandset.h \
    Utils/string.h \
    Compiler/params.h \
    Compiler/operand.h \
    Compiler/labeltable.h \
    compilern.h \
    Compiler/instruction.h \
    Compiler/line.h \
    Utils/searchresult.h \
    Compiler/pair.h \
    Compiler/register.h \
    Compiler/condition.h \
    Compiler/address.h \
    Compiler/data.h

RESOURCES += \
    resources.qrc

