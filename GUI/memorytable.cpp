#include "memorytable.h"

MemoryTable::MemoryTable(QWidget *parent) : QTableWidget(parent)
{
    this->setRowCount(ROWS);
    this->setColumnCount(COLUMNS);

    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setStretchLastSection(true);
    for (int i=0; i < this->verticalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem("0x" + QString::number(i * 16, 16));
        this->setVerticalHeaderItem(i, item);
    }

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->horizontalHeader()->setStretchLastSection(true);
    for (int i=0; i < this->horizontalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem("0x" + QString::number(i, 16));
        this->setHorizontalHeaderItem(i, item);
    }

    for (int i=0; i < this->horizontalHeader()->count(); i++)
    {
        for (int j=0; j < this->verticalHeader()->count(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem("ff");
            item->setTextAlignment(Qt::AlignCenter);
            this->setItem(j, i, item);
        }
    }

    this->setCurrentCell(0, 0);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MemoryTable::wheelEvent(QWheelEvent* event)
{
    int p = event->delta()/120; // +1 when scroll up, -1 when down

    int row = this->currentRow() - p;
    if (row < 0)
    {
        row = 0;
    }
    if (row >= ROWS-1)
    {
        row = ROWS-1;
    }

    this->setCurrentCell(row, this->currentColumn());
}
