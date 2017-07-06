#ifndef PRAM_H
#define PRAM_H

#include <QObject>

#include <vector>
#include <iostream>

class PRAM : public QObject
{
    Q_OBJECT
private:
    std::vector<unsigned int> table;

    const unsigned int pages;
    const unsigned int bytesPerPage = 256;
    const unsigned int maxPossiblePages = 16;

public:
    PRAM(unsigned int pages);
    virtual ~PRAM();

    void clearPRam();
    int getValue(unsigned int index) const;
    void setValue(unsigned int index, int value);

signals:
    void onPramChanged(unsigned index, unsigned value);
    void onPramClear();
};

#endif // PRAM_H
