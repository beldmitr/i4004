#ifndef DATARAMBANK_H
#define DATARAMBANK_H

#include <vector>
#include <iostream>
#include <memory>
#include "dataramchip.h"

class DataRAMBank
{
private:
    std::vector<std::shared_ptr<DataRAMChip>> chips;
    const int length;

public:
    DataRAMBank();
    std::shared_ptr<DataRAMChip> getDataRAMChip(int index);
};

#endif // DATARAMBANK_H
