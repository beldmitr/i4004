TEMPLATE = app
TARGET = Intel4004

BUILDDIR = "/Users/dima/dev/bak/build"
#MAKEFILE = $${BUILDDIR}/Makefile

Release:DESTDIR = $${BUILDDIR}/release
Release:OBJECTS_DIR = $${BUILDDIR}/release/.obj
Release:MOC_DIR = $${BUILDDIR}/release/.moc
Release:RCC_DIR = $${BUILDDIR}/release/.rcc
Release:UI_DIR = $${BUILDDIR}/release/.ui

Debug:DESTDIR = $${BUILDDIR}/debug
Debug:OBJECTS_DIR = $${BUILDDIR}/debug/.obj
Debug:MOC_DIR = $${BUILDDIR}/debug/.moc
Debug:RCC_DIR = $${BUILDDIR}/debug/.rcc
Debug:UI_DIR = $${BUILDDIR}/debug/.ui

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

SOURCES += \
    GUI/mainwindow.cpp \
    GUI/romwidget.cpp \
    GUI/subwindow.cpp \
    GUI/memorytable.cpp \
    GUI/chipdataram.cpp \
    main.cpp \
    Simulator/simulator.cpp \
    Simulator/rom.cpp \
    Simulator/dram.cpp \
    Simulator/cpu.cpp \
    Simulator/stack.cpp \
    Simulator/dataramregister.cpp \
    Simulator/dataramchip.cpp \
    Simulator/datarambank.cpp \
    Compiler/mathexpr.cpp \
    GUI/cpuwidget.cpp \
    GUI/button.cpp \
    GUI/coloredcombobox.cpp \
    GUI/chooseiowidget.cpp \
    GUI/editor.cpp \
    GUI/highlighter.cpp \
    GUI/editorsubwindow.cpp \
    GUI/ledsubwindow.cpp \
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
    GUI/ledimage.cpp \
    GUI/led.cpp \
    Compiler/firstpassline.cpp \
    GUI/debuggerlist.cpp \
    GUI/debuggersubwindow.cpp \
    Simulator/debugger.cpp

HEADERS += \
    GUI/mainwindow.h \
    GUI/romwidget.h \
    GUI/subwindow.h \
    GUI/memorytable.h \
    GUI/chipdataram.h \
    Simulator/simulator.h \
    Simulator/rom.h \
    Simulator/dram.h \
    Simulator/cpu.h \
    Simulator/stack.h \
    Simulator/dataramregister.h \
    Simulator/dataramchip.h \
    Simulator/datarambank.h \
    Compiler/mathexpr.h \
    GUI/cpuwidget.h \
    GUI/button.h \
    GUI/coloredcombobox.h \
    GUI/chooseiowidget.h \
    GUI/editor.h \
    GUI/highlighter.h \
    GUI/editorsubwindow.h \
    GUI/ledsubwindow.h \
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
    GUI/ledimage.h \
    GUI/led.h \
    Compiler/firstpassline.h \
    GUI/debuggerlist.h \
    GUI/debuggersubwindow.h \
    Simulator/debugger.h

RESOURCES += \
    resources.qrc

