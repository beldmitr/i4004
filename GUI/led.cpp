#include "led.h"

Led::Led(Simulator *simulator, QWidget *parent) : QWidget(parent)
{
    this->simulator = simulator;

    ledImage = std::shared_ptr<LedImage>(new LedImage);
    coloredComboBox = std::shared_ptr<ColoredComboBox>(new ColoredComboBox);
    connector = std::shared_ptr<ChooseIOWidget>(new ChooseIOWidget);

    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));
    layout->addWidget(coloredComboBox.get(), 0,0);
    layout->addWidget(ledImage.get(), 1,0);
    layout->addWidget(connector.get(), 2,0);

    //    ledImage->light(true);

    connect(coloredComboBox.get(), static_cast<void (QComboBox::*)(const QString&)>(&ColoredComboBox::activated),
            [=](const QString& color)
    {
        ledImage->setColor(color);
    });

    connect(connector.get(), &ChooseIOWidget::onROMConnected,
            [=](unsigned page, unsigned bit)
    {
        type = IOType::ROM_IO;
        this->page = page;
        this->bit = bit;

        if (type == IOType::ROM_IO && page == this->page)
        {
            bool isLight = (value & (int)pow(2,bit)) >> bit;
            this->ledImage->light(isLight);
        }

    });

    connect(connector.get(), &ChooseIOWidget::onDRAMConnected,
            [=](unsigned bank, unsigned chip, unsigned bit)
    {
        type = IOType::DRAM_IO;
        this->bank = bank;
        this->chip = chip;
        this->bit = bit;

        if (this->type == IOType::DRAM_IO && this->bank == bank && this->chip == chip)
        {
            bool isLight = (value & (int)pow(2, bit)) >> bit;
            this->ledImage->light(isLight);
        }
    });

    connect(connector.get(), &ChooseIOWidget::onDisconnected,
            [=]()
    {
        type = IOType::NONE;
        this->ledImage->light(false);
    });

    // Connect to Data RAM IO
    DRAM* dram = simulator->getDram().get();
    for (int i = 0; i < dram->getLength(); i++)
    {
        DataRAMBank* bank = dram->getDataRAMBank(i).get();
        for (int j = 0; j < bank->getLength(); j++)
        {
            DataRAMChip* chip = bank->getDataRAMChip(j).get();
            for (int k = 0; k < chip->getLength(); k++)
            {
                connect(chip, &DataRAMChip::onDramChipOutputChanged,
                        [=](unsigned bank, unsigned chip, unsigned value)
                {
                    this->value = value;

                    if (this->type == IOType::DRAM_IO && this->bank == bank && this->chip == chip)
                    {
                        bool isLight = (value & (int)pow(2,bit)) >> bit;
                        this->ledImage->light(isLight);
                    }

                });
            }
        }
    }

    // Connect to ROM
    ROM* rom = simulator->getRom().get();
    for (int i = 0; i < rom->getPages(); i++)
    {
        connect(rom, &ROM::onRomIOChanged, [=](unsigned page, unsigned value){
            this->value = value;

            if (type == IOType::ROM_IO && page == this->page)
            {
                bool isLight = (value & (int)pow(2,bit)) >> bit;
                this->ledImage->light(isLight);
            }
        });
    }



    //    simulator->getDram()->getDataRAMBank(0)->getDataRAMChip(0)->onDramChipOutputChanged();
    //    simulator->getRom()->onRomIOChanged();

}

Led::~Led()
{

}

