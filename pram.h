#ifndef PRAM_H
#define PRAM_H

#include <vector>
#include <iostream>

using namespace std;

class PRAM
{
private:
    std::vector<unsigned int> table;

    const unsigned int pages;
    const unsigned int bytesPerPage;
    const unsigned int maxPossiblePages;

public:
    PRAM(unsigned int pages);
    virtual ~PRAM();

    void clearPRam();
    int getValue(unsigned int index) const;
    void setValue(unsigned int index, int value);
};

#endif // PRAM_H
