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
#include <vector>

#include "Simulator/simulator.h"

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
private:
    std::shared_ptr<QGridLayout> layout;

    std::shared_ptr<QGroupBox> gbStack; // gb means GroupBox
    std::shared_ptr<QGridLayout> layoutStack;
    std::shared_ptr<QLabel> lblPC;  // lbl means Label
    std::shared_ptr<QLabel> lblLevel1;
    std::shared_ptr<QLabel> lblLevel2;
    std::shared_ptr<QLabel> lblLevel3;
    std::shared_ptr<QTextEdit> edtPC;   // edt means Edit
    std::shared_ptr<QTextEdit> edtLevel1;
    std::shared_ptr<QTextEdit> edtLevel2;
    std::shared_ptr<QTextEdit> edtLevel3;

    std::shared_ptr<QGroupBox> gbRegisters;
    std::shared_ptr<QGridLayout> layoutRegisters;
    std::vector<std::shared_ptr<QLabel>> lblR;
    std::vector<std::shared_ptr<QTextEdit>> edtR;

    std::shared_ptr<QGroupBox> gbOther;
    std::shared_ptr<QGridLayout> layoutOther;
    std::shared_ptr<QLabel> lblAccumulator;
    std::shared_ptr<QTextEdit> edtAccumulator;
    std::shared_ptr<QLabel> lblCarry;
    std::shared_ptr<QCheckBox> cbxCarry;    // cbx means CheckBox
    std::shared_ptr<QLabel> lblTest;
    std::shared_ptr<QCheckBox> cbxTest;
    std::shared_ptr<QLabel> lblInstruction;
    std::shared_ptr<QLabel> lblCycles;
    std::shared_ptr<QTextEdit> edtCycles;

    // Methods
    void createWidgetStack();
    void createWidgetRegisters();
    void createWidgetOther();

public:
    explicit CpuWidget(Simulator* simulator, QWidget *parent = 0);
    virtual ~CpuWidget();

    // Setters
    void setStackPC(unsigned int value);
    void setStackLevel1(unsigned int value);
    void setStackLevel2(unsigned int value);
    void setStackLevel3(unsigned int value);

    void setRegisters(unsigned int index, unsigned int value);

    void setAccumulator(unsigned int value);
    void setCarry(bool value);
    void setTest(bool value);
    void setInstruction(QString value);
    void setCycles(unsigned int value);

signals:

public slots:
};

#endif // CPUWIDGET_H
