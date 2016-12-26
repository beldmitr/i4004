#include "dataramwidget.h"

QWidget* DataRamWidget::addElements()
{
    QWidget *w = new QWidget();

    QHBoxLayout *layout = new QHBoxLayout(w);

    QGroupBox *memGBox = new QGroupBox("Memory");
    QGroupBox *statusGBox = new QGroupBox("Status");
    QGroupBox *outputGBox = new QGroupBox("Output");

    QGridLayout *layoutMem = new QGridLayout(memGBox);
    QGridLayout *layoutStatus = new QGridLayout(statusGBox);
    QVBoxLayout *layoutOutput = new QVBoxLayout(outputGBox);

    for (int i = 0; i < 16; i++)
    {
        QLabel *addr = new QLabel("0x" + QString::number(i, 16));
        layoutMem->addWidget(addr,0,i+1,1,1, Qt::AlignHCenter);
        addr->setMaximumHeight(10);

        for (int j = 0; j < 4; j++)
        {
            QLabel *addr = new QLabel("0x" + QString::number(j*(i+1), 16));
            layoutMem->addWidget(addr,j+1,0,1,1);
            addr->setAutoFillBackground(true);


            QLineEdit *cell = new QLineEdit("F");
            layoutMem->addWidget(cell,j+1,i+1,1,1);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        QLabel *addr = new QLabel("0x" + QString::number(i, 16));
        layoutStatus->addWidget(addr,0,i,1,1, Qt::AlignHCenter);
        addr->setMaximumHeight(10);

        for (int j = 0; j < 4; j++)
        {
            QLineEdit *cell = new QLineEdit("F");
            layoutStatus->addWidget(cell,j+1,i,1,1);
        }
    }

    for (int i=0; i < 4; i++)
    {
        QCheckBox *outputCB = new QCheckBox();
        outputCB->setCheckable(false);
        layoutOutput->addWidget(outputCB);
        layoutOutput->setAlignment(outputCB, Qt::AlignHCenter);
    }

    // Size policies
    QSizePolicy memSP = memGBox->sizePolicy();
    QSizePolicy statSP = statusGBox->sizePolicy();
    QSizePolicy outSP = outputGBox->sizePolicy();

    memSP.setHorizontalStretch(16);
    statSP.setHorizontalStretch(4);
    outSP.setHorizontalStretch(1);

    memGBox->setSizePolicy(memSP);
    statusGBox->setSizePolicy(statSP);
    outputGBox->setSizePolicy(outSP);

    // add widgets to layouts
    layout->addWidget(memGBox);
    layout->addWidget(statusGBox);
    layout->addWidget(outputGBox);

    w->setLayout(layout);
    return w;
}

DataRamWidget::DataRamWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    layout = new QHBoxLayout(this);
    tabDRam = new QTabWidget();
    scroll = new QScrollBar();

    for (int i=0; i<8; i++)
    {
        QTabWidget *tw = new QTabWidget();
        for (int j=0; j<4; j++)
        {
            QWidget *w = addElements();
            tw->addTab(w, "Chip " + QString::number(j));
        }
        tabDRam->addTab(tw, "Bank " + QString::number(i));
    }

    // scroll settings
    scroll->setMinimum(0);
    scroll->setMaximum(maxTabPos);


    layout->addWidget(tabDRam);
    layout->addWidget(scroll);

    // connects
    connect(tabDRam, &QTabWidget::currentChanged,
        [=](int value)
        {
            QTabWidget* w = (QTabWidget*)tabDRam->widget(value);
            int tabChipCurrent = w->currentIndex();

            scroll->setValue(value * 4 + tabChipCurrent);
        });

    for (int i=0; i<tabDRam->count(); i++)
    {
        QTabWidget* w = (QTabWidget*)tabDRam->widget(i);
        connect(w, &QTabWidget::currentChanged,
            [=](int value)
            {
                scroll->setValue(i * 4 + value);
            });
    }

    connect(scroll, SIGNAL(valueChanged(int)), this, SLOT(raiseTab(int)));
}

void DataRamWidget::paintEvent(QPaintEvent* /* event */)
{

}

void DataRamWidget::raiseTab(int value)
{
    // raise bank tab
    tabDRam->setCurrentIndex(value / 4);

    // raise chip tab
    QTabWidget* w = (QTabWidget*)tabDRam->widget(value / 4);
    w->setCurrentIndex(value % 4);
}

void DataRamWidget::wheelEvent(QWheelEvent* event)
{
    /*
     *   raise tabe when scrolling on a component
     */
    int p = event->delta()/120; // +1 when scroll up, -1 when down

    /*
     *  current scroll position
     *  it can be 0 - 31, because we have got 8 bank tabs and every bank tab has 4 chip tabs
     *  so 8 * 4 = 32.
    */
    int value = scroll->value() - p;

    if (value < 0)
        value = 0;
    if (value > 31)
        value = 31;

    // set value to scrollng element
    scroll->setValue(value);

    // raise tabs
    raiseTab(value);
}


