#ifndef DATARAMCHIP_H
#define DATARAMCHIP_H

#include <vector>
#include <iostream>
#include <memory>
#include "dataramregister.h"

class DataRAMChip
{
private:
    std::vector<std::shared_ptr<DataRAMRegister>> registers;
    int output;

    const int length;
public:
    DataRAMChip();

    std::shared_ptr<DataRAMRegister> getDataRAMRegister(int index);
    int getOutput() const;
    void setOutput(int value);
};

#endif // DATARAMCHIP_H
