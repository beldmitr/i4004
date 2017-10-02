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
    comboTitle->setMinimumWidth(150);

    scrollBar = std::shared_ptr<QScrollBar>(new QScrollBar);

    // Add Banks and Chips items to ComboBox
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            comboTitle->addItem(QString("Bank %1 Chip %2")
                                .arg(QString::number(i))
                                .arg(QString::number(j)));

            if (j == 3 && i != 7)
            {
                comboTitle->insertSeparator(5 * i + 4);
            }
        }
    }

    // scrollBar settings
    scrollBar->setMinimum(0);
    scrollBar->setMaximum(8 * 4 - 1); // must be the same as a count of items in ComboBox

    // Title layout
    titleLayout->addWidget(comboTitle.get());

    for(int i = 0; i < 8; i++)
    {    // 8 banks
        for (int j = 0; j < 4; j++)
        { // 4 chips in each bank
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

    connect(comboTitle.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),   /// TODO is it enaugh &QComboBox::currentIndexChanged ??
        [=](int index)
        {
            int i = index / 5; // bank
            int j = index % 5; // chip

            scrollBar->setValue(4 * i + j);

            // show choosen bank chip memory table
            for(ChipDataRam* g : chips)
            {
                g->hide();
            }
            ChipDataRam* gb = chips.at(4 * i + j);
            gb->show();
        });

    connect(scrollBar.get(), &QScrollBar::valueChanged,
        [=](int value)
        {
            comboTitle->setCurrentIndex(value + value / 4);

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
