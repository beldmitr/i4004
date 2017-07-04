#include "romwidget.h"

RomWidget::RomWidget(Simulator *simulator, QWidget *parent) : QWidget(parent)
{
    this->simulator = simulator;

    this->setAutoFillBackground(true);

    layout = std::shared_ptr<QVBoxLayout>(new QVBoxLayout(this));

    titleLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout);
    comboTitle = std::shared_ptr<QComboBox>(new QComboBox);

    for (int i = 0; i < 16; i++)
    {
        comboTitle->addItem(QString("Page %1: [0x%2 - 0x%3]")
                            .arg(QString::number(i))
                            .arg(QString::number(256 * i, 16))
                            .arg(QString::number(256 * (i + 1) - 1, 16)));
    }

    titleLayout->addWidget(comboTitle.get());
    titleLayout->addStretch();

    mainLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout);

    scroll = std::shared_ptr<QScrollBar>(new QScrollBar);

    memoryGB = std::shared_ptr<QGroupBox>(new QGroupBox);
    memLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(memoryGB.get()));

    memory = std::shared_ptr<MemoryTable>(new MemoryTable);
    memLayout->addWidget(memory.get());

    for (int j=0; j<16; j++)
    {
        QString pageNumber = QString::number(j);
        if (j < 10)
        {
            pageNumber.append("  ");
        }

        QGroupBox* ioGB = new QGroupBox("I/O " + pageNumber);
        QVBoxLayout* ioLayout = new QVBoxLayout(ioGB);

        for(int i=0; i<4; i++)
        {
            QCheckBox* ioCB = new QCheckBox();
            ioCB->setDisabled(true);
            ioLayout->addWidget(ioCB);
            ioLayout->setAlignment(ioCB, Qt::AlignHCenter);

            ioCB->setStyleSheet("QCheckBox::indicator:checked { background-color: #000; } "
                                  "QCheckBox::indicator {"
                                        "background-color: #FFF;"
                                        "border: 2px solid #000;"
                                  "}"
                                  "QCheckBox {"
                                        "color: #000;"
                                  "}");

            ios.push_back(ioCB);
        }

        memLayout->addWidget(ioGB);

        if (j==0)
        {
            activeIOGroupBox = ioGB;
        }
        else
        {
            ioGB->setVisible(false);
        }
    }

    scroll->setMinimum(0);
    scroll->setMaximum(255);
    setMemoryTitle(0);

    mainLayout->addWidget(memoryGB.get());
    mainLayout->addWidget(scroll.get());

    layout->addLayout(titleLayout.get());
    layout->addLayout(mainLayout.get());

    // connects
    connect(scroll.get(), &QScrollBar::valueChanged,
        [=](int value)
        {
            memory->setCurrentCell(value, memory->currentColumn());
            setMemoryTitle(value);
            setIOGroupBoxVisible(value);
        });

    connect(memory.get(), &QTableWidget::itemSelectionChanged,
        [=]()
        {
            int row = memory->currentRow();
            int column = memory->currentColumn();

            for (int i=0; i<memory->verticalHeader()->count(); i++)
            {
//                memory->verticalHeaderItem(i)->setText("0x" + QString::number(i * 16, 16));
                memory->verticalHeaderItem(i)->setText(QString::number(i * 16, 16));
            }

            scroll->setValue(row);

            selItem = memory->verticalHeaderItem(row);
//            selItem->setText("0x" + QString::number(row * 16 + column, 16));
            selItem->setText(QString::number(row * 16 + column, 16));

            setMemoryTitle(row);
            setIOGroupBoxVisible(row);
        });

    connect(comboTitle.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index)
        {
            scroll->setValue(index * 16);
        });

    // ROM
    ROM* rom = simulator->getRom().get();
    connect(rom, &ROM::onRomCleared,
            [=](){
               memory->clear();
            });

    connect(rom, &ROM::onRomChanged,
            [=](unsigned addr, unsigned value){
                memory->setValue(addr, value);
            });

    connect(rom, &ROM::onRomIOChanged,
            [=](unsigned page, unsigned value){
                this->setIO(page, value);
            });
}

RomWidget::~RomWidget()
{
    // delete or finalize here something
}

void RomWidget::setMemoryTitle(int value)
{
    // Uncomment this if you want a "Page Z [0xZZZ - 0xZZZ]" as a title of a GroupBox
//    memoryGB->setTitle("Page " + QString::number(value / 16) +
//                       " [ 0x" + QString::number(256 * (value / 16), 16) + " - 0x" +
//                       QString::number(256 * ((value / 16) + 1) - 1, 16) + " ]");

    comboTitle->setCurrentIndex(value / 16);
}

void RomWidget::setIOGroupBoxVisible(int value)
{
    QGroupBox* gb = (QGroupBox*)memLayout->itemAt(1 + value / 16)->widget();
    activeIOGroupBox->setVisible(false);
    gb->setVisible(true);
    activeIOGroupBox = gb;
}

void RomWidget::setIO(unsigned page, unsigned value)
{
    if (page > 7)
    {
        std::cerr << "RomWidget: setIO: Wrong page: " << page << std::endl;
        return; /// TODO make an exception
    }

    if (value > 0xf)
    {
        std::cerr << "RomWidget: setIO: Wrong value: " << value << std::endl;
        return; /// TODO make an exception
    }

    QCheckBox* io0 = ios.at(page + 0);
    QCheckBox* io1 = ios.at(page + 1);
    QCheckBox* io2 = ios.at(page + 2);
    QCheckBox* io3 = ios.at(page + 3);

    io0->setChecked(value & 0x1);
    io1->setChecked((value & 0x2) >> 1);
    io2->setChecked((value & 0x4) >> 2);
    io3->setChecked((value & 0x8) >> 3);
}

void RomWidget::write(std::vector<unsigned int> instructions)
{
    int i = 0;
    int j = 0;
    for(int ins : instructions)
    {
        int highByte = (ins & 0xFF00) >> 8;
        int lowByte = ins & 0xFF;

        if(highByte)
        {
            QString t;
            (highByte < 16) ? t.append("0") : t.append("");
            t.append(QString::number(highByte, 16));

            QTableWidgetItem* w = new QTableWidgetItem(t);
            w->setTextAlignment(Qt::AlignCenter);
            if (j > 15)
            {
                i++;
                j = 0;
            }
            memory->setItem(i, j, w);
            j++;
        }

        // write an instruction
        QString t;
        (lowByte < 16) ? t.append("0") : t.append("");
        t.append(QString::number(lowByte, 16));
        QTableWidgetItem* w = new QTableWidgetItem(t);
        w->setTextAlignment(Qt::AlignCenter);
        if (j > 15)
        {
            i++;
            j = 0;
        }
        memory->setItem(i, j, w);
        j++;
    }
}

void RomWidget::wheelEvent(QWheelEvent *event)
{
    int p = event->delta() / 120; // +1 when scroll up, -1 when down
    int newValue = scroll->value() - p;

    scroll->setValue(newValue);
}
