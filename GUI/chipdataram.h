#ifndef CHIPDATARAM_H
#define CHIPDATARAM_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QGridLayout>
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
    QGridLayout* outputLayout;

    std::vector<QTableWidgetItem*> headerItems;
    std::vector<QCheckBox*> outputs;
    std::vector<QTableWidgetItem*> memoryItems;
    std::vector<QTableWidgetItem*> statusItems;

    void setRegisterValue(unsigned int regNumber, unsigned int addr, unsigned int value);
    void setStatusValue(unsigned int regNumber, unsigned int addr, unsigned int value);

    void setOutputValue(unsigned int value);
signals:

private slots:
    void handleDramChipOutputChanged(unsigned bank, unsigned chip, unsigned value);
    void handleDramRegCharChanged(unsigned bank, unsigned chip, unsigned reg, unsigned addr, unsigned value);
    void handleDramRegStatChanged(unsigned bank, unsigned chip, unsigned reg, unsigned addr, unsigned value);
};

#endif // CHIPDATARAM_H
