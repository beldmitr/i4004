#include "dram.h"

DRAM::DRAM(int bankNumber) : QObject(),
    length(bankNumber)
{
    for (int i = 0; i < length; i++)
    {
        banks.push_back(std::shared_ptr<DataRAMBank>(new DataRAMBank()));
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
