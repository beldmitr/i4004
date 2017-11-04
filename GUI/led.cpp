#include "led.h"

Led::Led(Simulator *simulator, QWidget *parent) : QWidget(parent)
{
    this->simulator = simulator;

    ledImage = std::shared_ptr<LedImage>(new LedImage);
    coloredComboBox = std::shared_ptr<ColoredComboBox>(new ColoredComboBox);
    connector = std::shared_ptr<ChooseIOWidget>(new ChooseIOWidget(true));

    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));
//    layout->addWidget(coloredComboBox.get(),0, 0, Qt::AlignCenter);
    layout->addWidget(ledImage.get(), 1, 0, Qt::AlignCenter);
    layout->addWidget(connector.get(), 2, 0, Qt::AlignCenter);

    layout->setMargin(0);
    layout->setSpacing(10);
    layout->setHorizontalSpacing(0);

    connect(coloredComboBox.get(), static_cast<void (QComboBox::*)(const QString&)>(&ColoredComboBox::activated),
            [=](const QString& color)
    {
        ledImage->setColor(color);
    });

    connect(connector.get(), &ChooseIOWidget::onROMConnected,
            [=](unsigned page, unsigned bit)
    {
        type = ChooseIOWidget::IOType::ROM_IO;
        this->page = page;
        this->bit = bit;

        if (type == ChooseIOWidget::IOType::ROM_IO && page == this->page)
        {
            bool isLight = (value & (int)pow(2,bit)) >> bit;
            this->ledImage->light(isLight);
        }

    });

    connect(connector.get(), &ChooseIOWidget::onDRAMConnected,
            [=](unsigned bank, unsigned chip, unsigned bit)
    {
        type = ChooseIOWidget::IOType::DRAM_IO;
        this->bank = bank;
        this->chip = chip;
        this->bit = bit;

        if (this->type == ChooseIOWidget::IOType::DRAM_IO && this->bank == bank && this->chip == chip)
        {
            bool isLight = (value & (int)pow(2, bit)) >> bit;
            this->ledImage->light(isLight);
        }
    });

    connect(connector.get(), &ChooseIOWidget::onDisconnected,
            [=]()
    {
        type = ChooseIOWidget::IOType::NONE;
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
                connect(chip, SIGNAL(onDramChipOutputChanged(uint,uint,uint)), this, SLOT(handleDramChipOutputChanged(uint,uint,uint)));
            }
        }
    }

    // Connect to ROM
    ROM* rom = simulator->getRom().get();
    for (unsigned i = 0; i < rom->getPages(); i++)
    {
        connect(rom, SIGNAL(onRomIOChanged(uint,uint)), this, SLOT(handleRomIOChanged(uint,uint)));
    }
}

Led::~Led()
{

}

void Led::handleDramChipOutputChanged(unsigned bank, unsigned chip, unsigned value)
{
    this->value = value;

    if (this->type == ChooseIOWidget::IOType::DRAM_IO && this->bank == bank && this->chip == chip)
    {
        bool isLight = (value & (int)pow(2,bit)) >> bit;
        this->ledImage->light(isLight);
    }
}

void Led::handleRomIOChanged(unsigned page, unsigned value)
{
    this->value = value;

    if (type == ChooseIOWidget::IOType::ROM_IO && page == this->page)
    {
        bool isLight = (value & (int)pow(2,bit)) >> bit;
        this->ledImage->light(isLight);
    }
}

