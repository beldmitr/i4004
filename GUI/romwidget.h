#ifndef ROMWIDGET_H
#define ROMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QScrollBar>
#include <QGroupBox>
#include <QCheckBox>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QComboBox>

#include <vector>
#include <memory>

#include "Simulator/simulator.h"
#include "memorytable.h"

class RomWidget : public QWidget
{
    Q_OBJECT
private:
    const unsigned columnsNumber = 16;
    const unsigned pagesNumber = 16;
    const unsigned bytesPerPage = 256;
    const unsigned ioPerPage = 4;


    Simulator* simulator;

    std::shared_ptr<QGroupBox> memoryGB;    /// TODO make smart_ptr or delete
    std::shared_ptr<QVBoxLayout> layout;
    std::shared_ptr<QScrollBar> scroll;
    std::shared_ptr<QHBoxLayout> memLayout;
    QGroupBox* activeIOGroupBox; /// TODO wtf ????
    std::shared_ptr<QComboBox> comboTitle;
    std::shared_ptr<QGridLayout> titleLayout;
    std::shared_ptr<QHBoxLayout> mainLayout;

    std::vector<QCheckBox*> ios;

    std::shared_ptr<MemoryTable> memory;

    QTableWidgetItem* selItem;
    int lastRow = 0;

    void setMemoryTitle(int value);
    void setIOGroupBoxVisible(int value);

    void setIO(unsigned page, unsigned value);

public:
    explicit RomWidget(Simulator *simulator, QWidget *parent = 0);
    virtual ~RomWidget();

    void write(std::vector<unsigned int> instructions);


signals:

private slots:
    void handleRomCleared();
    void handleRomChanged(unsigned addr, unsigned value);
    void handleRomIOChanged(unsigned page, unsigned value);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // ROMWIDGET_H
