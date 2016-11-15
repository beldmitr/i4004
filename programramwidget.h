#ifndef PROGRAMRAMWIDGET_H
#define PROGRAMRAMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollBar>
#include <QComboBox>

#include "memorytable.h"

class ProgramRamWidget : public QWidget
{
    Q_OBJECT
private:
    QComboBox* comboTitle;
    QGroupBox* memoryGB;
    QVBoxLayout* layout;
    QScrollBar* scroll;
    QHBoxLayout* memLayout;

    QTableWidgetItem* selItem;

    void setMemoryTitle(int value);

public:
    explicit ProgramRamWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // PROGRAMRAMWIDGET_H
