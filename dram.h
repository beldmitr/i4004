#ifndef DRAM_H
#define DRAM_H

#include <vector>
#include <iostream>
#include <memory>

#include "datarambank.h"

class DRAM
{
private:
    std::vector<std::shared_ptr<DataRAMBank>> banks;

    const int length;

public:
    DRAM(int bankNumber);
    virtual ~DRAM();

    std::shared_ptr<DataRAMBank> getDataRAMBank(int index);
};

#endif // DRAM_H
