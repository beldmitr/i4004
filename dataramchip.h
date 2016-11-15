#ifndef DATARAMCHIP_H
#define DATARAMCHIP_H

#include <vector>
#include <iostream>
#include "dataramregister.h"

class DataRAMChip
{
private:
    std::vector<DataRAMRegister> registers;
    int output;

    const int length;
public:
    DataRAMChip();

    DataRAMRegister* getDataRAMRegister(int index);
    int getOutput() const;
    void setOutput(int value);
};

#endif // DATARAMCHIP_H
