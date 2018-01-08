#include "datarambank.h"

int DataRAMBank::getLength() const
{
    return length;
}

void DataRAMBank::reset()
{
    for (int i = 0; i < length; i++)
    {
        std::shared_ptr<DataRAMChip> chip = getDataRAMChip(i);
        chip->reset();
    }
}

DataRAMBank::DataRAMBank(unsigned int bank) : QObject()
{
    this->bank = bank;

    for (int i = 0; i < length; i++)
    {
        std::shared_ptr<DataRAMChip> chip = std::shared_ptr<DataRAMChip>(new DataRAMChip(bank, i));

        chips.push_back(chip);
    }

}

DataRAMBank::~DataRAMBank()
{
    // delete or finalize here something
}

std::shared_ptr<DataRAMChip> DataRAMBank::getDataRAMChip(int index)
{
    if (index < 0 || index > length-1)
    {
        std::cerr << "Error accessing Data RAM. " << index << " Data RAM Chip doesn't exist. There are "
                  << length << " chips." << std::endl;
        QString msg = QString("Error accessing Data RAM Chip.");
        throw LogExceptions("DataRamBank", msg.toStdString());
    }

    return chips[index];
}
