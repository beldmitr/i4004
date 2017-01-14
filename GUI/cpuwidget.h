#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>

#include "stackwidget.h"

/*
 *  I want to make widget like this:
 *
 *              stack layout                   registers layout
 *             /                              /
 *  ______________________________________________________________
 * |           STACK        |                REGISTERS            |
 * |      PC     0	0	0   |   R0	R1	0	0       R8	R9	0	0 |
 * | LEVEL 1     0	0	0   |   R2	R3	0	0       RA	RB	0	0 |
 * | LEVEL 2     0	0	0   |   R4	R5	0	0       RC	RD	0	0 |
 * | LEVEL 3     0	0	0   |   R6	R7	0	0       RE	RF	0	0 |
 * |--------------------------------------------------------------|
 * | ACCUMULATOR: 0 [0000]      CARRY:  V           TEST: V       | <- other layout
 * |                                                              |
 * | 000 00 NOP                                     CYCLES: 0     |
 *  --------------------------------------------------------------
 *
 * The example is on the web-site: http://e4004.szyc.org/emu/
 *
 *
 * To other layout is a VBoxLayout and consists of 2 HBoxLayouts.
 *  --------------------------------------------------------------
 * | ACCUMULATOR: 0 [0000]      CARRY:  V           TEST: V       | <- HBoxLayout
 * |--------------------------------------------------------------| <---- This all is VBoxLayout
 * | 000 00 NOP                                     CYCLES: 0     | <- HBoxLayout
 *  --------------------------------------------------------------
 *
 */

class CpuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CpuWidget(QWidget *parent = 0);
    virtual ~CpuWidget();

private:
    QGridLayout* layout;

    QGridLayout* stackLayout;
    QGridLayout* registersLayout;
    QVBoxLayout* otherLayout;

    StackWidget* stackWidget;

signals:

public slots:
};

#endif // CPUWIDGET_H
