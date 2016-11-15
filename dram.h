#ifndef DRAM_H
#define DRAM_H

#include <vector>
#include <iostream>
#include "datarambank.h"

class DRAM
{
private:
    std::vector<DataRAMBank> banks;

    const int length;

public:
    DRAM(int bankNumber);
    DataRAMBank* getDataRAMBank(int index);
};

#endif // DRAM_H
