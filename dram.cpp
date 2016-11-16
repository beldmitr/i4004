#include "dram.h"

DRAM::DRAM(int bankNumber) : length(bankNumber)
{
    for (int i = 0; i < length; i++) {
        banks.push_back(new DataRAMBank());
    }
}

DataRAMBank *DRAM::getDataRAMBank(int index)
{
    if (index < 0 || index > length) {
        std::cerr << "Data RAM accessing error. " << index
                  << " is wrong index of a bank, because there are " << length << " banks." << std::endl;
        throw "Data RAM accessing error.";
    }

    return banks[index];
}
