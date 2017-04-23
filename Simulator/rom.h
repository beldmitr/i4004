#ifndef ROM_H
#define ROM_H

#include <vector>
#include <iostream>
#include <string>

class ROM
{
private:
    unsigned int pages;
    const unsigned int bytesPerPage = 256;
    const unsigned int maxPossiblePages = 16;

    std::vector<unsigned int> table;
    std::vector<unsigned int> io;

    void setValue(unsigned int index, int value);

public:
    ROM(unsigned int pages);
    virtual ~ROM();

    void clearRom();
    void flashRom(std::vector<unsigned int> compiledCode);

    unsigned int getValue(unsigned int index) const;

    int getIO(unsigned int page) const;
    void setIO(unsigned int page, int value);
};

#endif // ROM_H
