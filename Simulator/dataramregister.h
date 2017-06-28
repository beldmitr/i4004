#ifndef DATARAMREGISTER_H
#define DATARAMREGISTER_H

#include <QObject>

#include <vector>
#include <iostream>

class DataRAMRegister : public QObject
{
    Q_OBJECT
private:
    std::vector<int> characters;
    std::vector<int> status;

    const int charactersLength = 16;
    const int statusLength = 4;

    unsigned int bank;
    unsigned int chip;
    unsigned int reg;    // register number

public:
    DataRAMRegister(unsigned int bank, unsigned int chip, unsigned int reg);
    virtual ~DataRAMRegister();

    void setCharacter(int index, int value);
    int getCharacter(int index) const;

    void setStatus(int index, int value);
    int getStatus(int index) const;

    int getCharactersLength() const;
    int getStatusLength() const;

signals:
    void onDramRegCharChanged(unsigned int bank, unsigned int chip, unsigned int reg, unsigned int index, unsigned int value);
    void onDramRegStatChanged(unsigned int bank, unsigned int chip, unsigned int reg, unsigned int index, unsigned int value);

};

#endif // DATARAMREGISTER_H
