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
    const int COLUMNS = 16;
    const int ROWS = 256;

    std::vector<QTableWidgetItem*> items;
    std::vector<QTableWidgetItem*> headerItems;

public:
    explicit MemoryTable(QWidget *parent = 0);
    virtual ~MemoryTable();

    void setValue(unsigned addr, unsigned value);
    void clear();

signals:

public slots:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *);
};

#endif // MEMORYTABLE_H
