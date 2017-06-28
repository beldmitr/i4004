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

    unsigned int bank;

public:
    DataRAMBank(unsigned int bank);
    virtual ~DataRAMBank();

    std::shared_ptr<DataRAMChip> getDataRAMChip(int index);

    int getLength() const;

signals:


};

#endif // DATARAMBANK_H
