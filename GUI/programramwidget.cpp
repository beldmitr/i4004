#include "programramwidget.h"


void ProgramRamWidget::setMemoryTitle(int value)
{
    comboTitle->setCurrentIndex(value / bytesPerPage);
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

    for (unsigned i = 0; i < pagesNumber; i++)
    {
        comboTitle->addItem(QString("Page %1: [0x%2 - 0x%3]")
                            .arg(QString::number(i))
                            .arg(QString::number(bytesPerPage * i, 16))
                            .arg(QString::number(bytesPerPage * (i + 1) - 1, 16)));
    }

    titleLayout->addWidget(comboTitle.get(), 0, 0, Qt::AlignCenter);

    mainLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout);
    scroll = std::shared_ptr<QScrollBar>(new QScrollBar);

    memoryGB = std::shared_ptr<QGroupBox>(new QGroupBox);
    memLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(memoryGB.get()));

    memory = std::shared_ptr<MemoryTable>(new MemoryTable(columnsNumber, pagesNumber, bytesPerPage));
    memLayout->addWidget(memory.get());

    scroll->setMinimum(0);
    scroll->setMaximum(pagesNumber * bytesPerPage - 1);

    this->setMemoryTitle(0);

    mainLayout->addWidget(memoryGB.get());
    mainLayout->addWidget(scroll.get());

    layout->addLayout(titleLayout.get());
    layout->addLayout(mainLayout.get());

    // connects
    connect(scroll.get(), &QScrollBar::valueChanged,
        [=](int value)
        {
            memory->setSelectedCell(value);

            this->setMemoryTitle(value);
        });

    connect(memory.get(), &QTableWidget::itemSelectionChanged,
        [=]()
        {
            int row = memory->currentRow();
            int column = memory->currentColumn();

            scroll->setValue(row * columnsNumber + column);

            this->setMemoryTitle(row * columnsNumber + column);
        });

    connect(comboTitle.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index)
        {
            scroll->setValue(index * bytesPerPage - columnsNumber);

            memory->setSelectedCell(index * bytesPerPage);
        });
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
