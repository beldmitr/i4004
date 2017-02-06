#include "chipdataram.h"

ChipDataRam::ChipDataRam(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    QGroupBox* inFrame = new QGroupBox;
    QHBoxLayout* inLayout = new QHBoxLayout(inFrame);

    // In Layout
    QTableWidget* memTable = new QTableWidget(4, 16);
    QTableWidget* statTable = new QTableWidget(4, 4);
    QGroupBox* outputFrame = new QGroupBox("Output");
    QVBoxLayout* outputLayout = new QVBoxLayout(outputFrame);

    // tables settings
    memTable->setSelectionMode(QAbstractItemView::SingleSelection);
    statTable->setSelectionMode(QAbstractItemView::SingleSelection);

    memTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    memTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    memTable->verticalHeader()->setStretchLastSection(false);
    memTable->horizontalHeader()->setStretchLastSection(false);
    for (int i=0; i < memTable->verticalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(i));
        memTable->setVerticalHeaderItem(i, item);
    }
    for (int i=0; i < memTable->horizontalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem("0x" + QString::number(i, 16));
        memTable->setHorizontalHeaderItem(i, item);
    }

    statTable->verticalHeader()->hide();
    statTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    statTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    statTable->verticalHeader()->setStretchLastSection(false);
    statTable->horizontalHeader()->setStretchLastSection(false);
    for (int i=0; i < statTable->horizontalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem("0x" + QString::number(i, 16));
        statTable->setHorizontalHeaderItem(i, item);
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
        QCheckBox* output = new QCheckBox;
        output->setCheckable(false);

        outputLayout->addWidget(output);
        outputLayout->setAlignment(output, Qt::AlignHCenter);
    }

    // add to in layout
    inLayout->addWidget(memTable);
    inLayout->addWidget(statTable);
    inLayout->addWidget(outputFrame);

    // add to layout
    layout->addWidget(inFrame);
}

ChipDataRam::~ChipDataRam()
{
    // delete or finalize here something
}
