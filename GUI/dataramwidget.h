#ifndef DATARAMWIDGETN_H
#define DATARAMWIDGETN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
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

#include "chipdataram.h"


class DataRamWidget : public QWidget
{
    Q_OBJECT
private:
    std::shared_ptr<QVBoxLayout> layout;
    std::shared_ptr<QHBoxLayout> titleLayout;
    std::shared_ptr<QHBoxLayout> memLayout;
    std::shared_ptr<QComboBox> comboTitle;
    std::shared_ptr<QScrollBar> scrollBar;
    std::vector<ChipDataRam*> chips;

public:
    explicit DataRamWidget(QWidget *parent = 0);
    virtual ~DataRamWidget();

signals:

public slots:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *);
};

#endif // DATARAMWIDGETN_H
