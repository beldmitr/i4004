#ifndef DATARAMWIDGET_H
#define DATARAMWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPalette>
#include <QGroupBox>
#include <QSizePolicy>
#include <QLineEdit>
#include <QCheckBox>
#include <QTableWidget>
#include <QScrollBar>
#include <QWheelEvent>
#include <QTabWidget>
#include <QGridLayout>

#include <iostream>

using namespace std;

/// TODO Delete old DataRam Widget
class DataRamWidget : public QWidget
{
    Q_OBJECT
private:
    const int maxTabPos = 31;

    QScrollBar* scroll;
    QTabWidget* tabDRam;
    QHBoxLayout* layout;

    QWidget* addElements();

public:
    explicit DataRamWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);

signals:


public slots:
    void raiseTab(int value);


};

#endif // DATARAMWIDGET_H
