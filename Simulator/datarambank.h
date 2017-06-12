#ifndef DATARAMBANK_H
#define DATARAMBANK_H

#include <QObject>

#include <vector>
#include <iostream>
#include <memory>
#include "dataramchip.h"

class DataRAMBank : public QObject
{
    Q_OBJECT
private:
    std::vector<std::shared_ptr<DataRAMChip>> chips;
    const int length = 4;

public:
    DataRAMBank();
    virtual ~DataRAMBank();

    std::shared_ptr<DataRAMChip> getDataRAMChip(int index);

};

#endif // DATARAMBANK_H
