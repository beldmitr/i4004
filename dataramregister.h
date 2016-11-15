#ifndef DATARAMREGISTER_H
#define DATARAMREGISTER_H

#include <vector>
#include <iostream>

class DataRAMRegister
{
private:
    std::vector<int> characters;
    std::vector<int> status;

    const int charactersLength;
    const int statusLength;

public:
    DataRAMRegister();

    void setCharacter(int index, int value);
    int getCharacter(int index) const;

    void setStatus(int index, int value);
    int getStatus(int index) const;
};

#endif // DATARAMREGISTER_H
