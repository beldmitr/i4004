#include "cpuwidget.h"

CpuWidget::CpuWidget(QWidget *parent) : QWidget(parent)
{
    layout = std::make_shared<QGridLayout>(this);

    createWidgetStack();
    createWidgetRegisters();
    createWidgetOther();
}

CpuWidget::~CpuWidget()
{
}

void CpuWidget::createWidgetStack()
{
    gbStack = std::make_shared<QGroupBox>("Stack");
    layoutStack = std::make_shared<QGridLayout>(gbStack.get());

    lblPC = std::make_shared<QLabel>("PC");
    lblLevel1 = std::make_shared<QLabel>("level 1");
    lblLevel2 = std::make_shared<QLabel>("level 2");
    lblLevel3 = std::make_shared<QLabel>("level 3");

    edtPC = std::make_shared<QTextEdit>();
    edtLevel1 = std::make_shared<QTextEdit>();
    edtLevel2 = std::make_shared<QTextEdit>();
    edtLevel3 = std::make_shared<QTextEdit>();

    edtPC->setReadOnly(true);
    edtLevel1->setReadOnly(true);
    edtLevel2->setReadOnly(true);
    edtLevel3->setReadOnly(true);

    edtPC->setFixedHeight(50);
    edtPC->setFixedWidth(250);
    edtLevel1->setFixedHeight(50);
    edtLevel1->setFixedWidth(250);
    edtLevel2->setFixedHeight(50);
    edtLevel2->setFixedWidth(250);
    edtLevel3->setFixedHeight(50);
    edtLevel3->setFixedWidth(250);

    layoutStack->addWidget(lblPC.get(), 0, 0);
    layoutStack->addWidget(lblLevel1.get(), 1, 0);
    layoutStack->addWidget(lblLevel2.get(), 2, 0);
    layoutStack->addWidget(lblLevel3.get(), 3, 0);

    layoutStack->addWidget(edtPC.get(), 0, 1);
    layoutStack->addWidget(edtLevel1.get(), 1, 1);
    layoutStack->addWidget(edtLevel2.get(), 2, 1);
    layoutStack->addWidget(edtLevel3.get(), 3, 1);

    layout->addWidget(gbStack.get(), 0, 0);
}

void CpuWidget::createWidgetRegisters()
{
    gbRegisters = std::make_shared<QGroupBox>("Registers");
    layoutRegisters = std::make_shared<QGridLayout>(gbRegisters.get());

    lblR0 = std::make_shared<QLabel>("R00");
    lblR1 = std::make_shared<QLabel>("R01");
    lblR2 = std::make_shared<QLabel>("R02");
    lblR3 = std::make_shared<QLabel>("R03");
    lblR4 = std::make_shared<QLabel>("R04");
    lblR5 = std::make_shared<QLabel>("R05");
    lblR6 = std::make_shared<QLabel>("R06");
    lblR7 = std::make_shared<QLabel>("R07");
    lblR8 = std::make_shared<QLabel>("R08");
    lblR9 = std::make_shared<QLabel>("R09");
    lblR10 = std::make_shared<QLabel>("R10");
    lblR11 = std::make_shared<QLabel>("R11");
    lblR12 = std::make_shared<QLabel>("R12");
    lblR13 = std::make_shared<QLabel>("R13");
    lblR14 = std::make_shared<QLabel>("R14");
    lblR15 = std::make_shared<QLabel>("R15");

    edtR0 = std::make_shared<QTextEdit>();
    edtR1 = std::make_shared<QTextEdit>();
    edtR2 = std::make_shared<QTextEdit>();
    edtR3 = std::make_shared<QTextEdit>();
    edtR4 = std::make_shared<QTextEdit>();
    edtR5 = std::make_shared<QTextEdit>();
    edtR6 = std::make_shared<QTextEdit>();
    edtR7 = std::make_shared<QTextEdit>();
    edtR8 = std::make_shared<QTextEdit>();
    edtR9 = std::make_shared<QTextEdit>();
    edtR10 = std::make_shared<QTextEdit>();
    edtR11 = std::make_shared<QTextEdit>();
    edtR12 = std::make_shared<QTextEdit>();
    edtR13 = std::make_shared<QTextEdit>();
    edtR14 = std::make_shared<QTextEdit>();
    edtR15 = std::make_shared<QTextEdit>();

    edtR0->setReadOnly(true);
    edtR1->setReadOnly(true);
    edtR2->setReadOnly(true);
    edtR3->setReadOnly(true);
    edtR4->setReadOnly(true);
    edtR5->setReadOnly(true);
    edtR6->setReadOnly(true);
    edtR7->setReadOnly(true);
    edtR8->setReadOnly(true);
    edtR9->setReadOnly(true);
    edtR10->setReadOnly(true);
    edtR11->setReadOnly(true);
    edtR12->setReadOnly(true);
    edtR13->setReadOnly(true);
    edtR14->setReadOnly(true);
    edtR15->setReadOnly(true);

    edtR0->setFixedHeight(50);
    edtR0->setFixedWidth(50);
    edtR1->setFixedHeight(50);
    edtR1->setFixedWidth(50);
    edtR2->setFixedHeight(50);
    edtR2->setFixedWidth(50);
    edtR3->setFixedHeight(50);
    edtR3->setFixedWidth(50);
    edtR4->setFixedHeight(50);
    edtR4->setFixedWidth(50);
    edtR5->setFixedHeight(50);
    edtR5->setFixedWidth(50);
    edtR6->setFixedHeight(50);
    edtR6->setFixedWidth(50);
    edtR7->setFixedHeight(50);
    edtR7->setFixedWidth(50);
    edtR8->setFixedHeight(50);
    edtR8->setFixedWidth(50);
    edtR9->setFixedHeight(50);
    edtR9->setFixedWidth(50);
    edtR10->setFixedHeight(50);
    edtR10->setFixedWidth(50);
    edtR11->setFixedHeight(50);
    edtR11->setFixedWidth(50);
    edtR12->setFixedHeight(50);
    edtR12->setFixedWidth(50);
    edtR13->setFixedHeight(50);
    edtR13->setFixedWidth(50);
    edtR14->setFixedHeight(50);
    edtR14->setFixedWidth(50);
    edtR15->setFixedHeight(50);
    edtR15->setFixedWidth(50);

    layoutRegisters->addWidget(lblR0.get(), 0, 0);
    layoutRegisters->addWidget(lblR1.get(), 0, 1);
    layoutRegisters->addWidget(edtR0.get(), 0, 2);
    layoutRegisters->addWidget(edtR1.get(), 0, 3);

    layoutRegisters->addWidget(lblR2.get(), 1, 0);
    layoutRegisters->addWidget(lblR3.get(), 1, 1);
    layoutRegisters->addWidget(edtR2.get(), 1, 2);
    layoutRegisters->addWidget(edtR3.get(), 1, 3);

    layoutRegisters->addWidget(lblR4.get(), 2, 0);
    layoutRegisters->addWidget(lblR5.get(), 2, 1);
    layoutRegisters->addWidget(edtR4.get(), 2, 2);
    layoutRegisters->addWidget(edtR5.get(), 2, 3);

    layoutRegisters->addWidget(lblR6.get(), 3, 0);
    layoutRegisters->addWidget(lblR7.get(), 3, 1);
    layoutRegisters->addWidget(edtR6.get(), 3, 2);
    layoutRegisters->addWidget(edtR7.get(), 3, 3);

    layoutRegisters->addWidget(lblR8.get(), 0, 4);
    layoutRegisters->addWidget(lblR9.get(), 0, 5);
    layoutRegisters->addWidget(edtR8.get(), 0, 6);
    layoutRegisters->addWidget(edtR9.get(), 0, 7);

    layoutRegisters->addWidget(lblR10.get(), 1, 4);
    layoutRegisters->addWidget(lblR11.get(), 1, 5);
    layoutRegisters->addWidget(edtR10.get(), 1, 6);
    layoutRegisters->addWidget(edtR11.get(), 1, 7);

    layoutRegisters->addWidget(lblR12.get(), 2, 4);
    layoutRegisters->addWidget(lblR13.get(), 2, 5);
    layoutRegisters->addWidget(edtR12.get(), 2, 6);
    layoutRegisters->addWidget(edtR13.get(), 2, 7);

    layoutRegisters->addWidget(lblR14.get(), 3, 4);
    layoutRegisters->addWidget(lblR15.get(), 3, 5);
    layoutRegisters->addWidget(edtR14.get(), 3, 6);
    layoutRegisters->addWidget(edtR15.get(), 3, 7);

    layout->addWidget(gbRegisters.get(), 0, 1);
}

void CpuWidget::createWidgetOther()
{
    gbOther = std::make_shared<QGroupBox>("");
    layoutOther = std::make_shared<QGridLayout>(gbOther.get());

    lblAccumulator = std::make_shared<QLabel>("Accumulator");
    edtAccumulator = std::make_shared<QTextEdit>();
    lblCarry = std::make_shared<QLabel>("Carry");
    cbxCarry = std::make_shared<QCheckBox>();
    lblTest = std::make_shared<QLabel>("Test");
    cbxTest = std::make_shared<QCheckBox>();
    lblInstruction = std::make_shared<QLabel>();
    lblCycles = std::make_shared<QLabel>("Cycles");
    edtCycles = std::make_shared<QTextEdit>();

    edtAccumulator->setReadOnly(true);
    edtCycles->setReadOnly(true);

    edtAccumulator->setFixedHeight(50);
    edtAccumulator->setFixedWidth(50);
    edtCycles->setFixedHeight(50);
    edtCycles->setFixedWidth(250);

    layoutOther->addWidget(lblAccumulator.get(), 0, 0);
    layoutOther->addWidget(edtAccumulator.get(), 0, 1);

    layoutOther->addWidget(lblCarry.get(), 0, 2);
    layoutOther->addWidget(cbxCarry.get(), 0, 3);

    layoutOther->addWidget(lblTest.get(), 0, 4);
    layoutOther->addWidget(cbxTest.get(), 0, 5);

    layoutOther->addWidget(lblInstruction.get(), 1, 0);

    layoutOther->addWidget(lblCycles.get(), 1, 4);
    layoutOther->addWidget(edtCycles.get(), 1, 5);

    layout->addWidget(gbOther.get(), 1, 0, 1, 2);
}






















