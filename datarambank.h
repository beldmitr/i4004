#ifndef DATARAMBANK_H
#define DATARAMBANK_H

#include <vector>
#include <iostream>
#include "dataramchip.h"

class DataRAMBank
{
private:
    std::vector<DataRAMChip> chips;
    const int length;

public:
    DataRAMBank();
    DataRAMChip* getDataRAMChip(int index);
};

#endif // DATARAMBANK_H
