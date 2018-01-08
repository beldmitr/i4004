#ifndef ROM_H
#define ROM_H

#include <QObject>

#include <vector>
#include <iostream>
#include <string>

#include "Utils/string.h"
#include "debugger.h"

#include "Exceptions/logexceptions.h"

class ROM : public QObject
{
    Q_OBJECT
private:
    unsigned int pages;
    const unsigned bytesPerPage = 256;
    const unsigned maxPossiblePages = 16;

    std::vector<unsigned> table;
    std::vector<unsigned> io;

    void setValue(unsigned addr, unsigned value);

public:
    ROM(unsigned pages);
    virtual ~ROM();

    void clearRom();
    void flashRom(std::vector<unsigned> compiledCode);
    void reset();

    unsigned int getValue(unsigned index) const;

    int getIO(unsigned page) const;
    void setIO(unsigned page, unsigned value);

    unsigned int getPages() const;

signals:
    void onRomChanged(unsigned addr, unsigned value);
    void onRomCleared();
    void onRomIOChanged(unsigned page, unsigned value);
};

#endif // ROM_H
