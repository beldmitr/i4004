#include "dataramwidget.h"

DataRamWidget::DataRamWidget(Simulator *simulator, QWidget *parent) : QWidget(parent)
{
    this->simulator = simulator;

    this->setAutoFillBackground(true);

    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));
    layout->setMargin(2);
    layout->setSpacing(0);
    layout->setHorizontalSpacing(0);

    titleLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout);
    memLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout);
    memLayout->setMargin(0);
    memLayout->setSpacing(0);

    comboTitle = std::shared_ptr<QComboBox>(new QComboBox);

    scrollBar = std::shared_ptr<QScrollBar>(new QScrollBar);

    // Add Banks and Chips items to ComboBox
    for (unsigned i = 0; i < banksNumber; i++)
    {
        for (unsigned j = 0; j < chipNumber; j++)
        {
            comboTitle->addItem(QString("Bank %1 Chip %2")
                                .arg(QString::number(i))
                                .arg(QString::number(j)));

            if (j == (chipNumber - 1) && i != (banksNumber - 1))
            {
                comboTitle->insertSeparator((chipNumber + 1) * i + chipNumber);
            }
        }
    }

    // scrollBar settings
    scrollBar->setMinimum(0);
    scrollBar->setMaximum(banksNumber * chipNumber - 1); // must be the same as a count of items in ComboBox

    // Title layout
    titleLayout->addWidget(comboTitle.get());

    for(unsigned i = 0; i < banksNumber; i++)
    {
        for (unsigned j = 0; j < chipNumber; j++)
        {
            ChipDataRam* chip = new ChipDataRam(simulator, i, j);

            // Memory layout
            memLayout->addWidget(chip);

            chips.push_back(chip);

            if (!(i == 0 && j == 0))
            {
                chip->hide();
            }
        }
    }

    memLayout->addWidget(scrollBar.get());

    // add to main layout
    layout->addLayout(titleLayout.get(), 0, 0, Qt::AlignCenter);
    layout->addLayout(memLayout.get(), 1, 0);

    // connects

    connect(comboTitle.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [=](int index)
        {
            int i = index / (chipNumber + 1); // bank
            int j = index % (chipNumber + 1); // chip

            scrollBar->setValue(chipNumber * i + j);

            // show choosen bank chip memory table
            for(ChipDataRam* g : chips)
            {
                g->hide();
            }
            ChipDataRam* gb = chips.at(chipNumber * i + j);
            gb->show();
        });

    connect(scrollBar.get(), &QScrollBar::valueChanged,
        [=](int value)
        {
            comboTitle->setCurrentIndex(value + value / chipNumber);

            // show choosen bank chip memory table
            for(ChipDataRam* g : chips)
            {
                g->hide();
            }
            ChipDataRam* gb = chips.at(value);
            gb->show();
        });
}

DataRamWidget::~DataRamWidget()
{
    for (ChipDataRam* chip : chips)
    {
        delete(chip);
    }
}

void DataRamWidget::wheelEvent(QWheelEvent* event)
{
    /// FIXME 120 is a magic number
    int p = event->delta() / 120; // +1 when scroll up, -1 when down
    int newValue = scrollBar->value() - p;

    scrollBar->setValue(newValue);
}
