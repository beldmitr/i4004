#include "dataramregister.h"

int DataRAMRegister::getCharactersLength() const
{
    return charactersLength;
}

int DataRAMRegister::getStatusLength() const
{
    return statusLength;
}

void DataRAMRegister::reset()
{
    for (unsigned i = 0; i < charactersLength; i++)
    {
        setCharacter(i, 0);
    }

    for (unsigned i = 0; i < statusLength; i++)
    {
        setStatus(i, 0);
    }
}

DataRAMRegister::DataRAMRegister(unsigned int bank, unsigned int chip, unsigned int reg) : QObject()
{
    this->bank = bank;
    this->chip = chip;
    this->reg = reg;

    for (unsigned i = 0; i < charactersLength; i++) {
        characters.push_back(0);
    }

    for (unsigned i = 0; i < statusLength; i++) {
        status.push_back(0);
    }
}

DataRAMRegister::~DataRAMRegister()
{
    // delete or finalize here something
}

void DataRAMRegister::setCharacter(unsigned index, unsigned value)
{
    if (index > charactersLength) {
        std::cerr << "A DataRAM Chip has got " << charactersLength << " registers. "
                  << index << " is bad index of a register." << std::endl;
        return;
    }

    if (value > 0xF) {
        std::cerr << "A DataRAM Register has got 4 bit characters, which can save [0x0 - 0xF] values. "
                  << value << " is bad value. It will reduce with a mask 0xF." << std::endl;
        value = value & 0xF;
    }

    characters[index] = value;

    emit onDramRegCharChanged(bank, chip, reg, index, value);
}

int DataRAMRegister::getCharacter(unsigned index) const
{
    if (index > charactersLength)
    {
        std::cerr << "A DataRAM Chip has got " << charactersLength << " registers. "
                  << index << " is bad index of a register." << std::endl;
        throw "DataRAM chip access error, because of wrong index"; /// FIXME Exception
    }

    return characters[index];
}

void DataRAMRegister::setStatus(unsigned index, unsigned value)
{
    if (index > statusLength)
    {
        std::cerr << "A DataRAM Chip has got " << statusLength << " status registers. "
                  << index << " is bad index of a status register." << std::endl;
        return;
    }

    if (value > 0xF)
    {
        std::cerr << "A DataRAM Register has got 4 bit characters, wgich can save [0x0 - 0xF] values. "
                  << value << " is bad value. It will reduce with a mask 0xF." << std::endl;
        value = value & 0xF;
    }

    status[index] = value;

    emit onDramRegStatChanged(bank, chip, reg, index, value);
}

int DataRAMRegister::getStatus(unsigned index) const
{
    if (index > statusLength)
    {
        std::cerr << "A DataRAM Chip has got " << statusLength << " status registers. "
                  << index << " is bad index of a register." << std::endl;
        throw "DataRAM chip access error, because of wrong index"; /// FIXME Exception
    }

    return status[index];
}
