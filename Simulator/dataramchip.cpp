#include "dataramchip.h"

DataRAMChip::DataRAMChip(unsigned int number) : QObject()
{
    this->chip = number;

    for (int i = 0; i < length; i++)
    {
        std::shared_ptr<DataRAMRegister> reg = std::shared_ptr<DataRAMRegister>(new DataRAMRegister(i));

        connect(reg.get(), &DataRAMRegister::onDramRegCharChanged,
                [=](unsigned int reg, unsigned int index, unsigned int value){
                    emit onDramRegCharChanged(this->chip, reg, index, value);
                });

        connect(reg.get(), &DataRAMRegister::onDramRegStatChanged,
                [=](unsigned int reg, unsigned int index, unsigned int value){
                    emit onDramRegStatChanged(this->chip, reg, index, value);
                });

        registers.push_back(reg);
    }


}

DataRAMChip::~DataRAMChip()
{
    // delete or finalize here something
}

std::shared_ptr<DataRAMRegister> DataRAMChip::getDataRAMRegister(int index)
{
    if (index < 0 || index > length-1)
    {
        std::cerr << "The number of registers in Data RAM Chip is " << length
                  << ". " << index << " is wrong number." << std::endl;
        throw "Data RAM access error. Wrong index of a register in a chip."; /// FIXME Exception
    }

    return registers[index];
}

int DataRAMChip::getOutput() const
{
    return output & 0xF;
}

void DataRAMChip::setOutput(int value)
{
    if (value < 0 || value > 0xF)
    {
        std::cerr << "Data RAM port is 4 bit and can store a value [0x0 - 0xF]. "
                  << value << " is wrong value." << std::endl;
        return;
    }

    output = value;

    emit onDramChipOutputChanged(chip, value);
}
