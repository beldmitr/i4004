#include "programramwidget.h"


void ProgramRamWidget::setMemoryTitle(int value)
{
    // Uncomment this if you want a "Page Z [0xZZZ - 0xZZZ]" as a title of a GroupBox
//    memoryGB->setTitle("Page " + QString::number(value / 16) +
//                       " [ 0x" + QString::number(256 * (value / 16), 16) + " - 0x" +
//                       QString::number(256 * ((value / 16) + 1) - 1, 16) + " ]");

    comboTitle->setCurrentIndex(value / 16);
}

ProgramRamWidget::ProgramRamWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);

    layout = new QVBoxLayout(this);

    QHBoxLayout* titleLayout = new QHBoxLayout;
    comboTitle = new QComboBox;

    for (int i = 0; i < 16; i++)
    {
        comboTitle->addItem(QString("Page %1: [0x%2 - 0x%3]")
                            .arg(QString::number(i))
                            .arg(QString::number(256 * i, 16))
                            .arg(QString::number(256 * (i + 1) - 1, 16)));
    }

    titleLayout->addWidget(comboTitle);
    titleLayout->addStretch();


    QHBoxLayout* mainLayout = new QHBoxLayout;
    scroll = new QScrollBar();

    memoryGB = new QGroupBox;
    memLayout = new QHBoxLayout(memoryGB);

    MemoryTable* memory = new MemoryTable;
    memLayout->addWidget(memory);

    scroll->setMinimum(0);
    scroll->setMaximum(255);
    setMemoryTitle(0);

    mainLayout->addWidget(memoryGB);
    mainLayout->addWidget(scroll);

    layout->addLayout(titleLayout);
    layout->addLayout(mainLayout);

    // connects
    connect(scroll, &QScrollBar::valueChanged,
        [=](int value)
        {
            memory->setCurrentCell(value, memory->currentColumn());
            setMemoryTitle(value);
        });

    connect(memory, &QTableWidget::itemSelectionChanged,
        [=]()
        {
            int row = memory->currentRow();
            int column = memory->currentColumn();

            for (int i=0; i<memory->verticalHeader()->count(); i++)
            {
//                memory->verticalHeaderItem(i)->setText("0x" + QString::number(i * 16, 16));
                memory->verticalHeaderItem(i)->setText(QString::number(i * 16, 16));
            }

            scroll->setValue(row);

            selItem = memory->verticalHeaderItem(row);
//            selItem->setText("0x" + QString::number(row * 16 + column, 16));
            selItem->setText(QString::number(row * 16 + column, 16));

            setMemoryTitle(row);
        });

    connect(comboTitle, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index)
        {
            scroll->setValue(index * 16);
        });
}
