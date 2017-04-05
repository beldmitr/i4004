#include "dataramwidget.h"

DataRamWidget::DataRamWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
//    this->setStyleSheet("DataRamWidgetN { border: 1px solid black }");

    QVBoxLayout* layout = new QVBoxLayout(this);

    QHBoxLayout* titleLayout = new QHBoxLayout;
    QHBoxLayout* memLayout = new QHBoxLayout;

    QComboBox* comboTitle = new QComboBox;

    scrollBar = new QScrollBar;

    // Add Banks and Chips items to ComboBox
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            comboTitle->addItem(QString("Bank %1\tChip %2\t")
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
    scrollBar->setMaximum(8*4 - 1); // must be the same as a count of items in ComboBox

    // Title layout
    titleLayout->addWidget(comboTitle);
    titleLayout->addStretch();

    for(int i = 0; i < 8; i++)
    {    // 8 banks
        for (int j = 0; j < 4; j++)
        { // 4 chips in each bank
            ChipDataRam* chip = new ChipDataRam;

            // Memory layout
            memLayout->addWidget(chip);

            chips.push_back(chip);

            if (!(i == 0 && j == 0))
            {
                chip->hide();
            }
        }
    }

    memLayout->addWidget(scrollBar);


    // add to main layout
    layout->addLayout(titleLayout);
    layout->addLayout(memLayout);

    // connects

    connect(comboTitle, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
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

    connect(scrollBar, &QScrollBar::valueChanged,
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
    // delete or finalize here something
}

void DataRamWidget::wheelEvent(QWheelEvent* event)
{
    int p = event->delta() / 120; // +1 when scroll up, -1 when down
    int newValue = scrollBar->value() - p;



    scrollBar->setValue(newValue);

//    int row = this->currentRow() - p;
//    if (row < 0)
//        row = 0;
//    if (row >= ROWS-1)
//        row = ROWS-1;

//    this->setCurrentCell(row, this->currentColumn());
}
