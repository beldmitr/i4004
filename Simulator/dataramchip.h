#ifndef DATARAMCHIP_H
#define DATARAMCHIP_H

#include <QObject>

#include <vector>
#include <iostream>
#include <memory>
#include "dataramregister.h"

class DataRAMChip : public QObject
{
    Q_OBJECT
private:
    std::vector<std::shared_ptr<DataRAMRegister>> registers;
    int output = 0;

    const int length = 4;

    unsigned int chip;

public:
    DataRAMChip(unsigned int chip);
    virtual ~DataRAMChip();

    std::shared_ptr<DataRAMRegister> getDataRAMRegister(int index);
    int getOutput() const;
    void setOutput(int value);

signals:
    void onDramChipOutputChanged(unsigned int chip, unsigned int value);

    void onDramRegCharChanged(unsigned int chip, unsigned int reg, unsigned int index, unsigned int value);
    void onDramRegStatChanged(unsigned int chip, unsigned int reg, unsigned int index, unsigned int value);
};

#endif // DATARAMCHIP_H
