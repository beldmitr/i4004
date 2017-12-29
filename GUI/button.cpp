#include "button.h"

Button::Button(Simulator* simulator, ChooseIOWidget *connector) : QPushButton()
{
    this->setMaximumSize(48, 48);

    this->simulator = simulator;

    this->setIcon(QIcon(":/Resources/components/button.png"));
    this->setIconSize(QSize(32,32));

    this->setCheckable(false);

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

    connect(this, &Button::pressed,
            [=]()
            {
                switch (type)
                {
                    case ChooseIOWidget::IOType::ROM_IO:
                        {
                            ROM* rom = simulator->getRom().get();
                            int value = rom->getIO(page);
                            value |= 1 << bit;
                            rom->setIO(page, value);
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

    connect(this, &Button::released,
            [=]()
            {

                switch (type)
                {
                    case ChooseIOWidget::IOType::ROM_IO:
                        {
                            ROM* rom = simulator->getRom().get();
                            int value = rom->getIO(page);
                            value &= ~(1 << bit);
                            rom->setIO(page, value);
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
