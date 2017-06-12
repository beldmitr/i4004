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

public:
    DataRAMChip();
    virtual ~DataRAMChip();

    std::shared_ptr<DataRAMRegister> getDataRAMRegister(int index);
    int getOutput() const;
    void setOutput(int value);

signals:
    void onDramChipChanged();
};

#endif // DATARAMCHIP_H
