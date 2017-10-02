#ifndef DATARAMWIDGETN_H
#define DATARAMWIDGETN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QTableWidget>
#include <QCheckBox>
#include <QHeaderView>
#include <QScrollBar>
#include <QComboBox>
#include <QWheelEvent>

#include <vector>
#include <memory>

#include "Simulator/simulator.h"
#include "chipdataram.h"


class DataRamWidget : public QWidget
{
    Q_OBJECT
private:
    Simulator* simulator; // I didn't create, I don't to delete

    std::shared_ptr<QGridLayout> layout;
    std::shared_ptr<QHBoxLayout> titleLayout;
    std::shared_ptr<QHBoxLayout> memLayout;
    std::shared_ptr<QComboBox> comboTitle;
    std::shared_ptr<QScrollBar> scrollBar;
    std::vector<ChipDataRam*> chips;

public:
    explicit DataRamWidget(Simulator* simulator, QWidget *parent = 0);
    virtual ~DataRamWidget();

signals:

public slots:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *);
};

#endif // DATARAMWIDGETN_H
