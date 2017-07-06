#include "button.h"

Button::Button(Simulator* simulator, ChooseIOWidget *connector) : QPushButton()
{
    this->simulator = simulator;

    this->setAutoFillBackground(true);
    this->setIcon(QIcon(":/Resources/components/button.png"));
    this->setIconSize(QSize(160, 160));

    this->setCheckable(true);

    this->setFlat(false);

    connect(connector, &ChooseIOWidget::onROMConnected,
            [=](unsigned page, unsigned bit)
    {
        type = ChooseIOWidget::IOType::ROM_IO;
        this->page = page;
        this->bit = bit;
    });

    connect(connector, &ChooseIOWidget::onDRAMConnected,
            [=](unsigned bank, unsigned chip, unsigned bit)
    {
        type = ChooseIOWidget::IOType::DRAM_IO;
        this->bank = bank;
        this->chip = chip;
        this->bit = bit;
    });

    connect(connector, &ChooseIOWidget::onDisconnected,
            [=]()
    {
        type = ChooseIOWidget::IOType::NONE;
    });

    connect(this, &Button::clicked,
            [=](bool checked)
            {
                switch (type)
                {
                    case ChooseIOWidget::IOType::ROM_IO:
                        {
                            ROM* rom = simulator->getRom().get();
                            int value = rom->getIO(page);
                            if (checked)
                            {
                                value |= 1 << bit;
                                rom->setIO(page, value);
                            }
                            else
                            {
                                value &= ~(1 << bit);
                                rom->setIO(page, value);
                            }

                            break;
                        }

                    case ChooseIOWidget::IOType::DRAM_IO:
                        {
                            DataRAMChip* dramChip = simulator->getDram()->getDataRAMBank(bank)->getDataRAMChip(chip).get();
                            int value = dramChip->getOutput();
                            dramChip->setOutput(value ^ (1 << bit));
                            break;
                        }
                    case ChooseIOWidget::IOType::NONE:

                        break;
                    default:
                        break;
                }
            });
}

Button::~Button()
{
    // delete here something
}
