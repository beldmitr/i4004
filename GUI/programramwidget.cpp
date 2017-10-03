#include "programramwidget.h"


void ProgramRamWidget::setMemoryTitle(int value)
{
    comboTitle->setCurrentIndex(value / 16);

    // PRAM
    PRAM* pram = simulator->getPram().get();
    connect(pram, SIGNAL(onPramClear()), this, SLOT(handlePramCleared()));

    connect(pram, SIGNAL(onPramChanged(uint,uint)), this, SLOT(handlePramChanged(uint,uint)));
}

ProgramRamWidget::ProgramRamWidget(Simulator* simulator, QWidget *parent) : QWidget(parent)
{
    this->simulator = simulator;

    this->setAutoFillBackground(true);

    layout = std::shared_ptr<QVBoxLayout>(new QVBoxLayout(this));
    layout->setMargin(2);
    layout->setSpacing(0);

    titleLayout = std::shared_ptr<QGridLayout>(new QGridLayout);
    comboTitle = std::shared_ptr<QComboBox>(new QComboBox);

    for (int i = 0; i < 16; i++)
    {
        comboTitle->addItem(QString("Page %1: [0x%2 - 0x%3]")
                            .arg(QString::number(i))
                            .arg(QString::number(256 * i, 16))
                            .arg(QString::number(256 * (i + 1) - 1, 16)));
    }

    titleLayout->addWidget(comboTitle.get(), 0, 0, Qt::AlignCenter);

    mainLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout);
    scroll = std::shared_ptr<QScrollBar>(new QScrollBar);

    memoryGB = std::shared_ptr<QGroupBox>(new QGroupBox);
    memLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(memoryGB.get()));

    memory = std::shared_ptr<MemoryTable>(new MemoryTable);
    memLayout->addWidget(memory.get());

    scroll->setMinimum(0);
    scroll->setMaximum(255);
    setMemoryTitle(0);

    mainLayout->addWidget(memoryGB.get());
    mainLayout->addWidget(scroll.get());

    layout->addLayout(titleLayout.get());
    layout->addLayout(mainLayout.get());

    // connects
    connect(scroll.get(), &QScrollBar::valueChanged,
        [=](int value)
        {
            memory->setCurrentCell(value, memory->currentColumn());
            setMemoryTitle(value);
        });

    connect(memory.get(), &QTableWidget::itemSelectionChanged,
        [=]()
        {
            int row = memory->currentRow();
            int column = memory->currentColumn();

            for (int i=0; i<memory->verticalHeader()->count(); i++)
            {
                memory->verticalHeaderItem(i)->setText(QString::number(i * 16, 16));
            }

            scroll->setValue(row);

            // I don't create this pointer with new, so I don't need to delete it
            QTableWidgetItem* selItem = memory->verticalHeaderItem(row);
            selItem->setText(QString::number(row * 16 + column, 16));
            /*
             * I didn't create selItem with "new" command so I do not need to delete it,
             * only assign to nullptr to disallow reusage or wrong usage of this pointer
             */
            selItem = nullptr;

            setMemoryTitle(row);
        });

    connect(comboTitle.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index)
        {
            scroll->setValue(index * 16);
        });

    PRAM* pram = simulator->getPram().get();
    connect(pram, SIGNAL(onPramChanged(uint,uint)), this, SLOT(handlePramChanged(uint,uint)));
}

ProgramRamWidget::~ProgramRamWidget()
{
    // delete or finalize here something
}

void ProgramRamWidget::handlePramCleared()
{
    memory->clear();
}

void ProgramRamWidget::handlePramChanged(unsigned addr, unsigned value)
{
    memory->setValue(addr, value);
}
