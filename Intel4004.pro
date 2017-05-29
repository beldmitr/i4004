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
    Simulator/simulator.cpp \
    Simulator/rom.cpp \
    Simulator/pram.cpp \
    Simulator/dram.cpp \
    Simulator/cpu.cpp \
    Simulator/stack.cpp \
    Simulator/dataramregister.cpp \
    Simulator/dataramchip.cpp \
    Simulator/datarambank.cpp \
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
    Compiler/instruction.cpp \
    Compiler/line.cpp \
    Utils/searchresult.cpp \
    Compiler/pair.cpp \
    Compiler/register.cpp \
    Compiler/condition.cpp \
    Compiler/address.cpp \
    Compiler/data.cpp \
    Compiler/constant.cpp \
    Compiler/objectcode.cpp \
    Exceptions/compilerexception.cpp \
    Exceptions/logexceptions.cpp \
    Compiler/compilererror.cpp \
    Compiler/compiler.cpp \
    i4004.cpp \
    GUI/autocompleter.cpp

HEADERS += \
    GUI/mainwindow.h \
    GUI/romwidget.h \
    GUI/programramwidget.h \
    GUI/subwindow.h \
    GUI/memorytable.h \
    GUI/chipdataram.h \
    Simulator/simulator.h \
    Simulator/rom.h \
    Simulator/pram.h \
    Simulator/dram.h \
    Simulator/cpu.h \
    Simulator/stack.h \
    Simulator/dataramregister.h \
    Simulator/dataramchip.h \
    Simulator/datarambank.h \
    Compiler/mathexpr.h \
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
    Compiler/instruction.h \
    Compiler/line.h \
    Utils/searchresult.h \
    Compiler/pair.h \
    Compiler/register.h \
    Compiler/condition.h \
    Compiler/address.h \
    Compiler/data.h \
    Compiler/constant.h \
    Compiler/objectcode.h \
    Exceptions/compilerexception.h \
    Exceptions/logexceptions.h \
    Compiler/compilererror.h \
    Compiler/compiler.h \
    i4004.h \
    GUI/autocompleter.h

RESOURCES += \
    resources.qrc

