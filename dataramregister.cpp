#include "dataramregister.h"

DataRAMRegister::DataRAMRegister() : charactersLength(16), statusLength(4)
{
    for (int i = 0; i < charactersLength; i++) {
        characters.push_back(0);
    }

    for (int i = 0; i < statusLength; i++) {
        status.push_back(0);
    }
}

void DataRAMRegister::setCharacter(int index, int value)
{
    if (index < 0 || index > charactersLength) {
        std::cerr << "A DataRAM Chip has got " << charactersLength << " registers. "
                  << index << " is bad index of a register." << std::endl;
        return;
    }

    if (value < 0 || value > 0xF) {
        std::cerr << "A DataRAM Register has got 4 bit characters, which can save [0x0 - 0xF] values. "
                  << value << " is bad value. It will reduce with a mask 0xF." << std::endl;
        value = value & 0xF;
    }

    characters[index] = value;
}

int DataRAMRegister::getCharacter(int index) const
{
    if (index < 0 || index > charactersLength)
    {
        std::cerr << "A DataRAM Chip has got " << charactersLength << " registers. "
                  << index << " is bad index of a register." << std::endl;
        throw "DataRAM chip access error, because of wrong index"; /// FIXME Exception
    }

    return characters[index];
}

void DataRAMRegister::setStatus(int index, int value)
{
    if (index < 0 || index > statusLength)
    {
        std::cerr << "A DataRAM Chip has got " << statusLength << " status registers. "
                  << index << " is bad index of a status register." << std::endl;
        return;
    }

    if (value < 0 || value > 0xF)
    {
        std::cerr << "A DataRAM Register has got 4 bit characters, wgich can save [0x0 - 0xF] values. "
                  << value << " is bad value. It will reduce with a mask 0xF." << std::endl;
        value = value & 0xF;
    }

    status[index] = value;
}

int DataRAMRegister::getStatus(int index) const
{
    if (index < 0 || index > statusLength)
    {
        std::cerr << "A DataRAM Chip has got " << statusLength << " status registers. "
                  << index << " is bad index of a register." << std::endl;
        throw "DataRAM chip access error, because of wrong index"; /// FIXME Exception
    }

    return status[index];
}
