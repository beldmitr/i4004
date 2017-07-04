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
#include <memory>

#include "Simulator/simulator.h"
#include "memorytable.h"

class RomWidget : public QWidget
{
    Q_OBJECT
private:
    Simulator* simulator;

    std::shared_ptr<QGroupBox> memoryGB;    /// TODO make smart_ptr or delete
    std::shared_ptr<QVBoxLayout> layout;
    std::shared_ptr<QScrollBar> scroll;
    std::shared_ptr<QHBoxLayout> memLayout;
    QGroupBox* activeIOGroupBox; /// TODO wtf ????
    std::shared_ptr<QComboBox> comboTitle;
    std::shared_ptr<QHBoxLayout> titleLayout;
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

public slots:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // ROMWIDGET_H
