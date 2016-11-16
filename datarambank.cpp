#include "datarambank.h"

DataRAMBank::DataRAMBank() : length(4)
{
    /// TODO remove 4 and write length
    for (int i = 0; i < 4; i++) {
        chips.push_back(new DataRAMChip());
    }
}

DataRAMChip* DataRAMBank::getDataRAMChip(int index)
{
    if (index < 0 || index > length-1) {
        std::cerr << "Error accessing Data RAM. " << index << " Data RAM Chip doesn't exist. There are "
                  << length << " chips." << std::endl;
        throw "Error accessing Data RAM Chip."; /// FIXME Exception
    }

    return chips[index];
}
