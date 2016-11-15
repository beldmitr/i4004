#include "pram.h"

int PRAM::getValue(unsigned int index) const {
    if(index > 4095) {
        cerr << "Program RAM memory has 4096 bytes, so it is possible to read cells from 0 to 4095. "
             << index << " is wrong address."  << endl;
        return -1;
    }

    return table.at(index);
}

void PRAM::setValue(unsigned int index, int value) {
    if(index > 4095) {
        cerr << "Program RAM memory has 4096 bytes, so it is possible to read cells from 0 to 4095. "
             << index << " is wrong address."  << endl;
        return;
    }

    if (!(value >= 0 && value < 0x100)) {
        cerr << "Program RAM is 8b memory, so it can be a 1B value (0-255) at a cell. "
             << value << " is wrong value." << endl;
        return;
    }

    table.at(index) = value;
}

void PRAM::clearPRam()
{
    table.clear();
}

void PRAM::setPRam(vector<int> table)
{
    if(table.size() > 4096) {
        cerr << "Program RAM memory can consider only 4096B." << table.size() << " is wrong size." << endl;
        return;
    }
    this->table = table;
}

PRAM::PRAM()
{

}
