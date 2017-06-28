#ifndef CHIPDATARAM_H
#define CHIPDATARAM_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QCheckBox>

#include "Simulator/simulator.h"

class ChipDataRam : public QWidget
{
    Q_OBJECT
public:
    explicit ChipDataRam(Simulator* simulator, unsigned int bank, unsigned int chip, QWidget *parent = 0);
    virtual ~ChipDataRam();

private:
    Simulator* simulator;

    unsigned int bank;
    unsigned int chip;

    QTableWidget* memTable;
    QTableWidget* statTable;

    QHBoxLayout* layout;
    QGroupBox* inFrame;
    QHBoxLayout* inLayout;
    QGroupBox* outputFrame;
    QVBoxLayout* outputLayout;

    std::vector<QTableWidgetItem*> headerItems;
    std::vector<QCheckBox*> outputs;
    std::vector<QTableWidgetItem*> memoryItems;
    std::vector<QTableWidgetItem*> statusItems;

    setRegisterValue(unsigned int regNumber, unsigned int addr, unsigned int value);
    setStatusValue(unsigned int regNumber, unsigned int addr, unsigned int value);

    void setOutputValue(unsigned int value);
signals:

public slots:
};

#endif // CHIPDATARAM_H
