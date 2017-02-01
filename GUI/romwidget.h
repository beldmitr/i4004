#ifndef ROMWIDGET_H
#define ROMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QScrollBar>
#include <QGroupBox>
#include <QCheckBox>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QComboBox>

#include <vector>

#include "memorytable.h"

class RomWidget : public QWidget
{
    Q_OBJECT
private:
    QGroupBox* memoryGB;
    QVBoxLayout* layout;
    QScrollBar* scroll;
    QHBoxLayout* memLayout;
    QGroupBox* activeIOGroupBox;
    QComboBox* comboTitle;

    MemoryTable* memory;

    QTableWidgetItem* selItem;
    int lastRow = 0;


    void setMemoryTitle(int value);
    void setIOGroupBoxVisible(int value);

public:
    explicit RomWidget(QWidget *parent = 0);
    virtual ~RomWidget();

    void clear();
    void write(std::vector<unsigned int> instructions);

signals:

public slots:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // ROMWIDGET_H
