#ifndef DATARAMCHIP_H
#define DATARAMCHIP_H

#include <QObject>

#include <vector>
#include <iostream>
#include <memory>

#include "dataramregister.h"
#include "Exceptions/logexceptions.h"

class DataRAMChip : public QObject
{
    Q_OBJECT
private:
    std::vector<std::shared_ptr<DataRAMRegister>> registers;
    int output = 0;
    const int length = 4;
    unsigned int bank;
    unsigned int chip;

public:
    DataRAMChip(unsigned int bank, unsigned int chip);
    virtual ~DataRAMChip();

    std::shared_ptr<DataRAMRegister> getDataRAMRegister(int index);
    int getOutput() const;
    void setOutput(int value);
    int getLength() const;
    void reset();

signals:
    void onDramChipOutputChanged(unsigned int bank, unsigned int chip, unsigned int value);
};

#endif // DATARAMCHIP_H
