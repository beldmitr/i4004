#include "datarambank.h"

DataRAMBank::DataRAMBank(unsigned int bank) : QObject()
{
    this->bank = bank;

    for (int i = 0; i < length; i++)
    {
        std::shared_ptr<DataRAMChip> chip = std::shared_ptr<DataRAMChip>(new DataRAMChip(i));

        connect(chip.get(), &DataRAMChip::onDramRegCharChanged,
        [=](unsigned int chip, unsigned int reg, unsigned int index, unsigned int value){
            emit onDramRegCharChanged(bank, chip, reg, index, value);
        });

        connect(chip.get(), &DataRAMChip::onDramRegStatChanged,
        [=](unsigned int chip, unsigned int reg, unsigned int index, unsigned int value){
            emit onDramRegStatChanged(bank, chip, reg, index, value);
        });

        connect(chip.get(), &DataRAMChip::onDramChipOutputChanged,
        [=](unsigned int chip, unsigned int value){
            emit onDramChipOutputChanged(bank, chip, value);
        });

        chips.push_back(chip);
    }

}

DataRAMBank::~DataRAMBank()
{
    // delete or finalize here something
}

std::shared_ptr<DataRAMChip> DataRAMBank::getDataRAMChip(int index)
{
    if (index < 0 || index > length-1)
    {
        std::cerr << "Error accessing Data RAM. " << index << " Data RAM Chip doesn't exist. There are "
                  << length << " chips." << std::endl;
        throw "Error accessing Data RAM Chip."; /// FIXME Exception
    }

    return chips[index];
}
