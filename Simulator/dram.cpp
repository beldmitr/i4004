#include "dram.h"

DRAM::DRAM(int bankNumber) : QObject(),
    length(bankNumber)
{
    for (int i = 0; i < length; i++)
    {
        std::shared_ptr<DataRAMBank> bank = std::shared_ptr<DataRAMBank>(new DataRAMBank(i));

        connect(bank.get(), &DataRAMBank::onDramChipOutputChanged,
        [=](unsigned int bank, unsigned int chip, unsigned int value){
            emit onDramChipOutputChanged(bank, chip, value);
        });

        connect(bank.get(), &DataRAMBank::onDramRegCharChanged,
        [=](unsigned int bank, unsigned int chip, unsigned int reg, unsigned int index, unsigned int value){
            emit onDramRegCharChanged(bank, chip, reg, index, value);
        });

        connect(bank.get(), &DataRAMBank::onDramRegStatChanged,
        [=](unsigned int bank, unsigned int chip, unsigned int reg, unsigned int index, unsigned int value){
            emit onDramRegStatChanged(bank, chip, reg, index, value);
        });

        banks.push_back(bank);
    }
}

DRAM::~DRAM()
{
    // delete or finalize here something
}

std::shared_ptr<DataRAMBank> DRAM::getDataRAMBank(int index)
{
    if (index < 0 || index > length)
    {
        std::cerr << "Data RAM accessing error. " << index
                  << " is wrong index of a bank, because there are " << length << " banks." << std::endl;
        throw "Data RAM accessing error.";  /// FIXME Exception
    }

    return banks[index];
}
