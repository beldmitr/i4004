#ifndef ROM_H
#define ROM_H

#include <vector>
#include <iostream>
#include <string>

class ROM
{
private:
    std::vector<unsigned int> table;
    std::vector<unsigned int> io;

    const unsigned int pages;
    const unsigned int bytesPerPage;

public:
    ROM(unsigned int pages);
    void clearRom();
    void flashRom(std::vector<unsigned int> compiledCode);

    int getValue(unsigned int index) const;
    void setValue(unsigned int index, int value);

    int getIO(unsigned int page) const;
    void setIO(unsigned int page, int value);
};

#endif // ROM_H
