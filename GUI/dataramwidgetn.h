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

#include "chipdataram.h"

using namespace std;    /// TODO remove std

class DataRamWidgetN : public QWidget
{
    Q_OBJECT
private:
    QScrollBar* scrollBar;  /// TODO smart_ptr or delete it
    vector<ChipDataRam*> chips; /// TODO smart_ptr or delete it

public:
    explicit DataRamWidgetN(QWidget *parent = 0);
    virtual ~DataRamWidgetN();

signals:

public slots:

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *);
};

#endif // DATARAMWIDGETN_H
