#include "programramwidget.h"


void ProgramRamWidget::setMemoryTitle(int value)
{
    /// Uncomment this if you want a "Page Z [0xZZZ - 0xZZZ]" as a title of a GroupBox
//    memoryGB->setTitle("Page " + QString::number(value / 16) +
//                       " [ 0x" + QString::number(256 * (value / 16), 16) + " - 0x" +
//                       QString::number(256 * ((value / 16) + 1) - 1, 16) + " ]");

    comboTitle->setCurrentIndex(value / 16);
}

ProgramRamWidget::ProgramRamWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);

    layout = std::shared_ptr<QVBoxLayout>(new QVBoxLayout(this));

    titleLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout);
    comboTitle = std::shared_ptr<QComboBox>(new QComboBox);

    for (int i = 0; i < 16; i++)
    {
        comboTitle->addItem(QString("Page %1: [0x%2 - 0x%3]")
                            .arg(QString::number(i))
                            .arg(QString::number(256 * i, 16))
                            .arg(QString::number(256 * (i + 1) - 1, 16)));
    }

    titleLayout->addWidget(comboTitle.get());
    titleLayout->addStretch();


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
}

ProgramRamWidget::~ProgramRamWidget()
{
    // delete or finalize here something
}
