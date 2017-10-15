#include "memorytable.h"

MemoryTable::MemoryTable(unsigned columnsNumber, unsigned pages, unsigned bytesPerPage) : QTableWidget()
{
    this->columnsNumber = columnsNumber;
    rowsNumber = pages * bytesPerPage / columnsNumber;

    this->setRowCount(rowsNumber);
    this->setColumnCount(columnsNumber);

    // Set vertical header (rows)
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setStretchLastSection(false);
    for (unsigned i = 0; i < rowsNumber; i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(i * columnsNumber, 16));
        this->setVerticalHeaderItem(i, item);

        headerItems.push_back(item);
    }

    // Set horizontal header (columns)
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->horizontalHeader()->setStretchLastSection(false);
    for (unsigned i = 0; i < columnsNumber; i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(i, 16));
        this->setHorizontalHeaderItem(i, item);

        headerItems.push_back(item);
    }

    for (unsigned i = 0; i < columnsNumber; i++)
    {
        for (unsigned j = 0; j < rowsNumber; j++)
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

    connect(this, &QTableWidget::itemSelectionChanged,
            [=]() {
        int row = this->currentRow();
        int column = this->currentColumn();

        for (unsigned i = 0; i < rowsNumber; i++)
        {
            this->verticalHeaderItem(i)->setText(QString::number(i * columnsNumber, 16));
        }

        // I don't create this pointer with new, so I don't need to delete it
        QTableWidgetItem* selItem = this->verticalHeaderItem(row);
        selItem->setText(QString::number(row * columnsNumber + column, 16));
        /*
         * I didn't create selItem with "new" command so I do not need to delete it,
         * only assign to nullptr to disallow reusage or wrong usage of this pointer
         */
        selItem = nullptr;
    });
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
    int row = addr / columnsNumber;
    int col = addr % columnsNumber;

    QTableWidgetItem* item = this->item(row, col);
    item->setText(QString::number(value, 16));
}

void MemoryTable::setSelectedCell(unsigned addr)
{
    int row = addr / columnsNumber;
    int col = this->currentColumn();

    this->setCurrentCell(row, col);
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
    int p = event->delta() / 120; // +1 when scroll up, -1 when down

    int row = this->currentRow() - p;
    if (row < 0)
    {
        row = 0;
    }
    if ((unsigned)row >= rowsNumber - 1)
    {
        row = rowsNumber - 1;
    }

    this->setCurrentCell(row, this->currentColumn());
}
