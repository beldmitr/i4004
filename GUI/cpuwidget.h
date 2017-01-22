#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTextEdit>
#include <QCheckBox>

#include <memory>

/*
 *  I want to make widget like this:
 *
 *  ______________________________________________________________
 * |           STACK        |                REGISTERS            |
 * |      PC     0	0	0   |   R0	R1	0	0       R8	R9	0	0 |
 * | LEVEL 1     0	0	0   |   R2	R3	0	0       RA	RB	0	0 |
 * | LEVEL 2     0	0	0   |   R4	R5	0	0       RC	RD	0	0 |
 * | LEVEL 3     0	0	0   |   R6	R7	0	0       RE	RF	0	0 |
 * |--------------------------------------------------------------|
 * | ACCUMULATOR: 0 [0000]      CARRY:  V           TEST: V       |
 * |                                                              |
 * | 000 00 NOP                                     CYCLES: 0     |
 *  --------------------------------------------------------------
 *
 * The example is on the web-site: http://e4004.szyc.org/emu/
 *
 */

class CpuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CpuWidget(QWidget *parent = 0);
    virtual ~CpuWidget();

    void createWidgetStack();
    void createWidgetRegisters();
    void createWidgetOther();

private:
    std::shared_ptr<QGridLayout> layout;

    std::shared_ptr<QGroupBox> gbStack;
    std::shared_ptr<QGridLayout> layoutStack;
    std::shared_ptr<QLabel> lblPC;
    std::shared_ptr<QLabel> lblLevel1;
    std::shared_ptr<QLabel> lblLevel2;
    std::shared_ptr<QLabel> lblLevel3;
    std::shared_ptr<QTextEdit> edtPC;
    std::shared_ptr<QTextEdit> edtLevel1;
    std::shared_ptr<QTextEdit> edtLevel2;
    std::shared_ptr<QTextEdit> edtLevel3;

    std::shared_ptr<QGroupBox> gbRegisters;
    std::shared_ptr<QGridLayout> layoutRegisters;
    std::shared_ptr<QLabel> lblR0;
    std::shared_ptr<QLabel> lblR1;
    std::shared_ptr<QLabel> lblR2;
    std::shared_ptr<QLabel> lblR3;
    std::shared_ptr<QLabel> lblR4;
    std::shared_ptr<QLabel> lblR5;
    std::shared_ptr<QLabel> lblR6;
    std::shared_ptr<QLabel> lblR7;
    std::shared_ptr<QLabel> lblR8;
    std::shared_ptr<QLabel> lblR9;
    std::shared_ptr<QLabel> lblR10;
    std::shared_ptr<QLabel> lblR11;
    std::shared_ptr<QLabel> lblR12;
    std::shared_ptr<QLabel> lblR13;
    std::shared_ptr<QLabel> lblR14;
    std::shared_ptr<QLabel> lblR15;

    std::shared_ptr<QTextEdit> edtR0;
    std::shared_ptr<QTextEdit> edtR1;
    std::shared_ptr<QTextEdit> edtR2;
    std::shared_ptr<QTextEdit> edtR3;
    std::shared_ptr<QTextEdit> edtR4;
    std::shared_ptr<QTextEdit> edtR5;
    std::shared_ptr<QTextEdit> edtR6;
    std::shared_ptr<QTextEdit> edtR7;
    std::shared_ptr<QTextEdit> edtR8;
    std::shared_ptr<QTextEdit> edtR9;
    std::shared_ptr<QTextEdit> edtR10;
    std::shared_ptr<QTextEdit> edtR11;
    std::shared_ptr<QTextEdit> edtR12;
    std::shared_ptr<QTextEdit> edtR13;
    std::shared_ptr<QTextEdit> edtR14;
    std::shared_ptr<QTextEdit> edtR15;

    std::shared_ptr<QGroupBox> gbOther;
    std::shared_ptr<QGridLayout> layoutOther;
    std::shared_ptr<QLabel> lblAccumulator;
    std::shared_ptr<QTextEdit> edtAccumulator;
    std::shared_ptr<QLabel> lblCarry;
    std::shared_ptr<QCheckBox> cbxCarry;
    std::shared_ptr<QLabel> lblTest;
    std::shared_ptr<QCheckBox> cbxTest;
    std::shared_ptr<QLabel> lblInstruction;
    std::shared_ptr<QLabel> lblCycles;
    std::shared_ptr<QTextEdit> edtCycles;

signals:

public slots:
};

#endif // CPUWIDGET_H
