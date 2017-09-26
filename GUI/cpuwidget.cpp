#include "cpuwidget.h"

CpuWidget::CpuWidget(Simulator *simulator, QWidget *parent) : QWidget(parent)
{    
    this->simulator = simulator;
    cpu = simulator->getCpu().get();
    stack = cpu->getStack();

    layout = std::make_shared<QGridLayout>();

    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);

    createWidgetStack();
    createWidgetRegisters();
    createWidgetOther();

     this->setLayout(layout.get());

    // connects
    connect(stack, SIGNAL(onStackChanged()), this, SLOT(handleStackChanged()));

    connect(cpu, SIGNAL(onCpuChanged()), this, SLOT(handleCpuChanged()));

//    connect(simulator, SIGNAL(onActualCommand(QString)), this, SLOT(handleActualCommand(QString)));

}

CpuWidget::~CpuWidget()
{
    // delete or finalize here something
}

void CpuWidget::createWidgetStack()
{
    gbStack = std::make_shared<QGroupBox>("Stack");
    layoutStack = std::make_shared<QGridLayout>(gbStack.get());

//    gbStack->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    lblPC = std::make_shared<QLabel>("PC");
    lblLevel1 = std::make_shared<QLabel>("Level 1");
    lblLevel2 = std::make_shared<QLabel>("Level 2");
    lblLevel3 = std::make_shared<QLabel>("Level 3");

    edtPC = std::make_shared<QLineEdit>("");
    edtLevel1 = std::make_shared<QLineEdit>("");
    edtLevel2 = std::make_shared<QLineEdit>("");
    edtLevel3 = std::make_shared<QLineEdit>("");

    edtPC->setReadOnly(true);
    edtPC->setFixedWidth(75);
//    edtPC->setFontWeight(QFont::Bold);
    edtPC->setText("0");

    edtLevel1->setReadOnly(true);
    edtLevel1->setFixedWidth(75);
    edtLevel1->setText("0");

    edtLevel2->setReadOnly(true);
    edtLevel2->setFixedWidth(75);
    edtLevel2->setText("0");

    edtLevel3->setReadOnly(true);
    edtLevel3->setFixedWidth(75);
    edtLevel3->setText("0");

    layoutStack->addWidget(lblPC.get(), 0, 0);
    layoutStack->addWidget(edtPC.get(), 0, 1);
    layoutStack->addWidget(lblLevel1.get(), 1, 0);
    layoutStack->addWidget(lblLevel2.get(), 2, 0);
    layoutStack->addWidget(lblLevel3.get(), 3, 0);

    layoutStack->addWidget(edtLevel1.get(), 1, 1);
    layoutStack->addWidget(edtLevel2.get(), 2, 1);
    layoutStack->addWidget(edtLevel3.get(), 3, 1);

    layout->addWidget(gbStack.get(), 0, 0);
}

void CpuWidget::createWidgetRegisters()
{
    gbRegisters = std::make_shared<QGroupBox>("Registers");
    layoutRegisters = std::make_shared<QGridLayout>(gbRegisters.get());

//    gbRegisters->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    for (int i = 0; i < 16; i++)
    {
        QString text = (i < 10) ?
                    QString("0").append(QString::number(i))
                  : QString::number(i);
        lblR.push_back(std::make_shared<QLabel>(text));
    }

    for (int i = 0; i < 16; i++)
    {
        edtR.push_back(std::shared_ptr<QLineEdit>(new QLineEdit("0")));
    }

    for (int i = 0; i < 16; i++)
    {
        edtR[i]->setReadOnly(true);
        edtR[i]->setFixedWidth(25);
    }

    for (int i = 0; i < 16; i+=2)
    {
        layoutRegisters->addWidget((lblR[i]).get(),   (i/2) % 4, (i/8) * 8 + 0);
        layoutRegisters->addWidget((lblR[i+1]).get(), (i/2) % 4, (i/8) * 8 + 1);
        layoutRegisters->addWidget((edtR[i]).get(),   (i/2) % 4, (i/8) * 8 + 2);
        layoutRegisters->addWidget((edtR[i+1]).get(), (i/2) % 4, (i/8) * 8 + 3);
    }

    layout->addWidget(gbRegisters.get(), 0, 1);
}

void CpuWidget::createWidgetOther()
{
    gbOther = std::make_shared<QGroupBox>("");
    layoutOther = std::make_shared<QGridLayout>(gbOther.get());

//    gbOther->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    lblAccumulator = std::make_shared<QLabel>("Accumulator");
    edtAccumulator = std::shared_ptr<QLineEdit>(new QLineEdit("0"));

    lblCarry = std::make_shared<QLabel>("Carry");
    cbxCarry = std::shared_ptr<QCheckBox>(new QCheckBox);


    lblTest = std::make_shared<QLabel>("Test");
    cbxTest = std::shared_ptr<QCheckBox>(new QCheckBox);

//    lblInstruction = std::make_shared<QLabel>("");
//    lblInstruction->setFixedWidth(300);

    lblCycles = std::make_shared<QLabel>("Cycles");
    edtCycles = std::make_shared<QLineEdit>("0");

    edtAccumulator->setReadOnly(true);
    edtAccumulator->setFixedWidth(25);
    edtCycles->setReadOnly(true);
    cbxCarry->setEnabled(false);
    cbxTest->setEnabled(false);

    QString styleCheckBox("QCheckBox::indicator:checked { background-color: #000; } "
                          "QCheckBox::indicator {"
                          "background-color: #FFF;"
                          "border: 2px solid #000;"
                          "}"
                          "QCheckBox {"
                          "color: #000;"
                          "}");
    cbxCarry->setStyleSheet(styleCheckBox);
    cbxTest->setStyleSheet(styleCheckBox);

    layoutOther->addWidget(lblAccumulator.get(), 0, 0);
    layoutOther->addWidget(edtAccumulator.get(), 0, 1);

    layoutOther->addWidget(lblCarry.get(), 0, 2, Qt::AlignRight);
    layoutOther->addWidget(cbxCarry.get(), 0, 3, Qt::AlignHCenter);

    layoutOther->addWidget(lblTest.get(), 0, 4, Qt::AlignRight);
    layoutOther->addWidget(cbxTest.get(), 0, 5, Qt::AlignHCenter);

//    layoutOther->addWidget(lblInstruction.get(), 1, 0);   //TODO new class Debugger, and DebuggerList of instructions, for now I don't need this

    layoutOther->addWidget(lblCycles.get(), 1, 0);
    layoutOther->addWidget(edtCycles.get(), 1, 1, 1, 5);

    layout->addWidget(gbOther.get(), 1, 0, 1, 2);
}

void CpuWidget::setStackPC(unsigned int value)
{
    edtPC->setText(QString::number(value, 16));
}

void CpuWidget::setStackLevel1(unsigned int value)
{
    edtLevel1->setText(QString::number(value, 16));
}

void CpuWidget::setStackLevel2(unsigned int value)
{
    edtLevel2->setText(QString::number(value, 16));
}

void CpuWidget::setStackLevel3(unsigned int value)
{
    edtLevel3->setText(QString::number(value, 16));
}

void CpuWidget::setRegisters(unsigned int index, unsigned int value)
{
    edtR[index]->setText(QString::number(value, 16));
}

void CpuWidget::setAccumulator(unsigned int value)
{
    edtAccumulator->setText(QString::number(value, 16));
}

void CpuWidget::setCarry(bool value)
{
    cbxCarry->setChecked(value);
}

void CpuWidget::setTest(bool value)
{
    cbxTest->setChecked(value);
}

//void CpuWidget::setInstruction(QString value)
//{
//    lblInstruction->setText(value);
//}

void CpuWidget::setCycles(unsigned int value)
{
    edtCycles->setText(QString::number(value, 16));
}

void CpuWidget::handleStackChanged()
{
    std::vector<int> registers = stack->getRegisters();

    unsigned int pointer = stack->getActualPointer();

    for (unsigned int i = 0; i < registers.size(); i++)
    {
        int address = registers[i];

        QFont font;

        if (pointer == i)
        {
            font.setBold(true);
        }
        else
        {
            font.setBold(false);
        }

        switch(i)
        {
        case 0:
            edtPC->setText(QString::number(address, 16));
            edtPC->setFont(font);
            break;
        case 1:
            edtLevel1->setText(QString::number(address, 16));
            edtLevel1->setFont(font);
            break;
        case 2:
            edtLevel2->setText(QString::number(address, 16));
            edtLevel2->setFont(font);
            break;
        case 3:
            edtLevel3->setText(QString::number(address, 16));
            edtLevel3->setFont(font);
            break;
        }
    }
}

void CpuWidget::handleCpuChanged()
{
    for (unsigned int i = 0; i < cpu->getCountRegisters(); i++)
    {
        std::shared_ptr<QLineEdit> edit = edtR[i];
        unsigned int value = cpu->getRegisterAt(i);
        edit->setText(QString::number(value, 16));
    }

    unsigned int acc = cpu->getAcc();
    edtAccumulator->setText(QString::number(acc, 16));

    cbxCarry->setChecked((bool)cpu->getCarry());

    cbxTest->setChecked((bool)cpu->getTest());

    edtCycles->setText(QString::number(cpu->getCycles(), 16));
}

//void CpuWidget::handleActualCommand(const QString& cmd)
//{
//    lblInstruction->setText(cmd);
//}
