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
    QComboBox* comboTitle;  /// TODO smart_ptr or delete
    QGroupBox* memoryGB;
    QVBoxLayout* layout;
    QScrollBar* scroll;
    QHBoxLayout* memLayout;

    QTableWidgetItem* selItem;

    void setMemoryTitle(int value);

public:
    explicit ProgramRamWidget(QWidget *parent = 0);
    virtual ~ProgramRamWidget();

signals:

public slots:
};

#endif // PROGRAMRAMWIDGET_H
