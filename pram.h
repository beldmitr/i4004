#ifndef PRAM_H
#define PRAM_H

#include <vector>
#include <iostream>

using namespace std;

class PRAM
{
private:
    vector<int> table;

public:
    PRAM();

    void clearPRam();
    void setPRam(vector<int> table);
    int getValue(unsigned int index) const;
    void setValue(unsigned int index, int value);
};

#endif // PRAM_H
