#ifndef ROM_H
#define ROM_H

#include <vector>
#include <iostream>

class ROM
{
private:
    std::vector<int> table;
    std::vector<int> io;

    const unsigned int pages;
    const unsigned int bytesPerPage;

public:
    ROM(int pages);
    void clearRom();
    void setRom(std::vector<int> table);

    int getValue(unsigned int index) const;
    void setValue(unsigned int index, int value);

    int getIO(unsigned int page) const;
    void setIO(unsigned int page, int value);
};

#endif // ROM_H
