#include "memorytable.h"

MemoryTable::MemoryTable(QWidget *parent) : QTableWidget(parent)
{
    this->setRowCount(ROWS);
    this->setColumnCount(COLUMNS);

    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setStretchLastSection(false);
    for (int i=0; i < this->verticalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(i * 16, 16));
        this->setVerticalHeaderItem(i, item);

        headerItems.push_back(item);
    }

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->horizontalHeader()->setStretchLastSection(false);
    for (int i=0; i < this->horizontalHeader()->count(); i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(i, 16));
        this->setHorizontalHeaderItem(i, item);

        headerItems.push_back(item);
    }

    for (int i=0; i < this->horizontalHeader()->count(); i++)
    {
        for (int j=0; j < this->verticalHeader()->count(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem("0");
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            this->setItem(j, i, item);

            items.push_back(item);
        }
    }

    this->setCurrentCell(0, 0);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setSelectionMode(QAbstractItemView::SingleSelection);
}

MemoryTable::~MemoryTable()
{
    for (QTableWidgetItem* item : headerItems)
    {
        delete (item);
    }

    for (QTableWidgetItem* item : items)
    {
        delete (item);
    }
}

void MemoryTable::setValue(unsigned addr, unsigned value)
{
    int row = addr / 16;
    int col = addr % 16;

    QTableWidgetItem* item = this->item(row, col);
    item->setText(QString::number(value, 16));
}

void MemoryTable::clear()
{
    for (unsigned i = 0; i < items.size(); i++)
    {
        this->setValue(i, 0);
    }
}

void MemoryTable::wheelEvent(QWheelEvent* event)
{
    /// FIXME magic number 120
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
