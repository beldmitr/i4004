#include "chipdataram.h"

ChipDataRam::ChipDataRam(Simulator* simulator, unsigned int bank, unsigned int chip, QWidget *parent) : QWidget(parent)
{
    this->simulator = simulator;
    this->bank = bank;
    this->chip = chip;

    layout = new QHBoxLayout(this);

    inFrame = new QGroupBox;
    inLayout = new QHBoxLayout(inFrame);

    // In Layout
    memTable = new QTableWidget(4, 16);
    statTable = new QTableWidget(4, 4);
    outputFrame = new QGroupBox("Output "+QString::number(bank)+"/"+QString::number(chip));
    outputLayout = new QVBoxLayout(outputFrame);

    // Tables settings
    // Memory Table
    memTable->setSelectionMode(QAbstractItemView::SingleSelection);
    statTable->setSelectionMode(QAbstractItemView::SingleSelection);

    memTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    memTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    memTable->verticalHeader()->setStretchLastSection(false);
    memTable->horizontalHeader()->setStretchLastSection(false);

    // Fill left header of memory table
    for (int i=0; i < memTable->verticalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(i, 16));
        memTable->setVerticalHeaderItem(i, item);
        headerItems.push_back(item);
    }

    // Fill top header of memory table
    for (int i = 0; i < memTable->horizontalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(i, 16));
        memTable->setHorizontalHeaderItem(i, item);
        headerItems.push_back(item);
    }

    //  Fill items memory
    for (int i = 0; i < memTable->verticalHeader()->count(); i++)
    {
        for (int j = 0; j < memTable->horizontalHeader()->count(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem("0");
            memTable->setItem(i, j,item);
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            item->setTextAlignment(Qt::AlignCenter);

            memoryItems.push_back(item);
        }
    }

    // Status table
    statTable->verticalHeader()->hide();
    statTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    statTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    statTable->verticalHeader()->setStretchLastSection(false);
    statTable->horizontalHeader()->setStretchLastSection(false);

    // Fill top header of stat table
    for (int i=0; i < statTable->horizontalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(i, 16));
        statTable->setHorizontalHeaderItem(i, item);
    }

    //  Fill items status
    for (int i = 0; i < statTable->verticalHeader()->count(); i++)
    {
        for (int j = 0; j < statTable->horizontalHeader()->count(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem("0");
            statTable->setItem(i, j, item);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

            statusItems.push_back(item);
        }
    }

    memTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    statTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    memTable->setMinimumHeight(120);
    statTable->setMinimumHeight(120);

    // size policies
    QSizePolicy sp;
    sp = memTable->sizePolicy();
    sp.setHorizontalStretch(100);
    memTable->setSizePolicy(sp);

    sp = statTable->sizePolicy();
    sp.setHorizontalStretch(25);
    statTable->setSizePolicy(sp);

    // make output checkboxes
    for (int i = 0; i < 4; i++)
    {
        QCheckBox* output = new QCheckBox(QString::number(i, 16));
        output->setLayoutDirection(Qt::RightToLeft);
        output->setStyleSheet("QCheckBox::indicator:checked { background-color: #000; } "
                              "QCheckBox::indicator {"
                                    "background-color: #FFF;"
                                    "border: 2px solid #000;"
                              "}"
                              "QCheckBox {"
                                    "color: #000;"
                              "}");
        outputs.push_back(output);
        output->setEnabled(false);

        outputLayout->addWidget(output);
        outputLayout->setAlignment(output, Qt::AlignHCenter);
    }

    // add to in layout
    inLayout->addWidget(memTable);
    inLayout->addWidget(statTable);
    inLayout->addWidget(outputFrame);

    // add to layout
    layout->addWidget(inFrame);

    // connects
    DRAM* dram = simulator->getDram().get();
    for (int i=0; i < dram->getLength(); i++)
    {
        DataRAMBank* bank = dram->getDataRAMBank(i).get();

        for (int j = 0; j < bank->getLength(); j++)
        {
            DataRAMChip* chip = bank->getDataRAMChip(j).get();
            connect(chip, SIGNAL(onDramChipOutputChanged(uint,uint,uint)), this, SLOT(handleDramChipOutputChanged(uint,uint,uint)));

            for (int k = 0; k < chip->getLength(); k++)
            {
                DataRAMRegister* reg = chip->getDataRAMRegister(k).get();
                connect(reg, SIGNAL(onDramRegCharChanged(uint,uint,uint,uint,uint)), this, SLOT(handleDramRegCharChanged(uint,uint,uint,uint,uint)));
                connect(reg, SIGNAL(onDramRegStatChanged(uint,uint,uint,uint,uint)), this, SLOT(handleDramRegStatChanged(uint,uint,uint,uint,uint)));
            }
        }
    }
}

ChipDataRam::~ChipDataRam()
{
    for (QTableWidgetItem* item : statusItems)
    {
        delete (item);
    }

    for (QTableWidgetItem* item : memoryItems)
    {
        delete (item);
    }

    for (QCheckBox* checkBox : outputs)
    {
        delete (checkBox);
    }

    for (QTableWidgetItem* item : headerItems)
    {
        delete (item);
    }

    delete(outputLayout);
    delete(outputFrame);
    delete(statTable);
    delete(memTable);
    delete(inLayout);
    delete(inFrame);
    delete(layout);
}

void ChipDataRam::setRegisterValue(unsigned int regNumber, unsigned int addr, unsigned int value)
{
    if (value > 0xF)
    {
        QString msg("ChipDataRam: setRegisterValue, value is too big.");
        std::cerr << msg.toStdString() << std::endl;
        throw msg;
    }

    QTableWidgetItem* item = memTable->item(regNumber, addr);
    item->setText(QString::number(value, 16));
}

void ChipDataRam::setStatusValue(unsigned int regNumber, unsigned int addr, unsigned int value)
{
    if (value > 0xF)
    {
        QString msg("ChipDataRam: setStatusValue, value is too big.");
        std::cerr << msg.toStdString() << std::endl;
        throw msg;
    }

    QTableWidgetItem* item = statTable->item(regNumber, addr);
    item->setText(QString::number(value, 16));
}

void ChipDataRam::setOutputValue(unsigned int value)
{
    if (value > 0xF)
    {
        QString msg("ChipDataRam: setOutputValue, value is too big.");
        std::cerr << msg.toStdString() << std::endl;
        throw msg;
    }

    for (unsigned i = 0; i < outputs.size(); i++)
    {
        QCheckBox* output = outputs.at(i);
        bool checked = ((value & (int)pow(2, i)) != 0);
        output->setChecked(checked);
    }
}

void ChipDataRam::handleDramChipOutputChanged(unsigned bank, unsigned chip, unsigned value)
{
    if (bank == this->bank && chip == this->chip)
    {
        this->setOutputValue(value);
    }
}

void ChipDataRam::handleDramRegCharChanged(unsigned bank, unsigned chip, unsigned reg, unsigned addr, unsigned value)
{
    if (bank == this->bank && chip == this->chip)
    {
        this->setRegisterValue(reg, addr, value);
    }
}

void ChipDataRam::handleDramRegStatChanged(unsigned bank, unsigned chip, unsigned reg, unsigned addr, unsigned value)
{
    if (bank == this->bank && chip == this->chip)
    {
        this->setStatusValue(reg, addr, value);
    }
}
