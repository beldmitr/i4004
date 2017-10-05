#ifndef MEMORYTABLE_H
#define MEMORYTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QWheelEvent>

class MemoryTable : public QTableWidget
{
    Q_OBJECT
private:
    unsigned columnsNumber;

    unsigned rowsNumber;

    std::vector<QTableWidgetItem*> items;
    std::vector<QTableWidgetItem*> headerItems;

public:
    explicit MemoryTable(unsigned columnsNumber, unsigned pages, unsigned bytesPerPage);
    virtual ~MemoryTable();

    void setValue(unsigned addr, unsigned value);
    void setSelectedCell(unsigned addr);
    void clear();

signals:

public slots:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *);

};

#endif // MEMORYTABLE_H
