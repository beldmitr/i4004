#ifndef PROCESSORWIDGET_H
#define PROCESSORWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QCheckBox>
#include <QLabel>

#include "cpumodel.h"


class ProcessorWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit ProcessorWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // PROCESSORWIDGET_H
