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

    const unsigned charactersLength = 16;
    const unsigned statusLength = 4;

    unsigned bank;
    unsigned chip;
    unsigned reg;    // register number

public:
    DataRAMRegister(unsigned int bank, unsigned int chip, unsigned int reg);
    virtual ~DataRAMRegister();

    void setCharacter(unsigned index, unsigned value);
    int getCharacter(unsigned index) const;

    void setStatus(unsigned index, unsigned value);
    int getStatus(unsigned index) const;

    int getCharactersLength() const;
    int getStatusLength() const;

    void reset();

signals:
    void onDramRegCharChanged(unsigned int bank, unsigned int chip, unsigned int reg, unsigned int index, unsigned int value);
    void onDramRegStatChanged(unsigned int bank, unsigned int chip, unsigned int reg, unsigned int index, unsigned int value);

};

#endif // DATARAMREGISTER_H
