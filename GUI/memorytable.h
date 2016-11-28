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

public:
    explicit MemoryTable(QWidget *parent = 0);

signals:

public slots:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *);
};

#endif // MEMORYTABLE_H
