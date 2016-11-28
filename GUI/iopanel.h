#ifndef IOPANEL_H
#define IOPANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QScrollArea>
#include <QListWidget>
#include <QSplitter>
#include <QSizePolicy>
#include <QDragEnterEvent>

#include "GUI/iowidget.h"
#include "GUI/iolistcomponents.h"

#include <iostream>

class IOPanel : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout* layout;
    ioWidget* viewArea;
    ioListComponents* lstComponents;
    QSplitter* splitter;

public:
    explicit IOPanel(QWidget *parent = 0);

    ioWidget* getIOWidget();

signals:

public slots:
};

#endif // IOPANEL_H
