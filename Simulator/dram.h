#ifndef DRAM_H
#define DRAM_H

#include <QObject>

#include <vector>
#include <iostream>
#include <memory>

#include "datarambank.h"
#include "Exceptions/logexceptions.h"

class DRAM : public QObject
{
    Q_OBJECT
private:
    std::vector<std::shared_ptr<DataRAMBank>> banks;

    const int length;

public:
    DRAM(int bankNumber);
    virtual ~DRAM();

    std::shared_ptr<DataRAMBank> getDataRAMBank(int index);

    int getLength() const;

    void reset();
};

#endif // DRAM_H
