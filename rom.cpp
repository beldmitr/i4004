#include "rom.h"

ROM::ROM(int pages) : pages(pages), bytesPerPage(256)
{
    clearRom();
}

int ROM::getValue(unsigned int index) const {
    if(index > 4095) {
        std::cerr << "ROM memory has 4096 bytes, so it is possible to read cells from 0 to 4095. "
             << index << " is wrong address."  << std::endl;
        return -1; /// FIXME make with Exception
    }

    return table[index];
}

void ROM::setValue(unsigned int index, int value) {
    if(index > 4095) {
        std::cerr << "ROM memory has 4096 bytes, so it is possible to read cells from 0 to 4095. "
             << index << " is wrong address."  << std::endl;
        return;
    }

    if (!(value >= 0 && value < 0x100)) {
        std::cerr << "ROM is 8b memory, so it can be a 1B value (0-255) at a cell. "
             << value << " is wrong value." << std::endl;
        return;
    }

    table[index] = value;
}

void ROM::clearRom()
{
    for (int i = 0; i < pages * bytesPerPage; i++) {
        table.push_back(0);
    }

    for (int i = 0; i < pages; i++) {
        io.push_back(0);
    }
}

void ROM::setRom(std::vector<int> table)
{
    if(table.size() > 4096) {
        std::cerr << "ROM memory can consider only 4096B." << table.size() << " is wrong size." << std::endl;
        return;
    }
    this->table = table;
}

int ROM::getIO(unsigned int page) const {
    if (page > pages) {
        std::cerr << "There are " << pages << " pages in ROM. " << page << " is bad value." << std::endl;
        throw "Wrong access to ROM";
    }
    return io[page] & 0xF;
}

void ROM::setIO(unsigned int page, int value) {
    if (page > pages) {
        std::cerr << "There are " << pages << " pages in ROM. " << page << " is bad value." << std::endl;
        return;
    }

    if (value < 0 || value > 0xF) {
        std::cerr << value << " is wrong value of ROM IO. ROM IO is 4 bit. Value will be reduced by 0xF mask."
                  << std::endl;
    }

    io[page] = value & 0xF;
}
