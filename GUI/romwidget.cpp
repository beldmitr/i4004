#include "romwidget.h"

RomWidget::RomWidget(Simulator *simulator, QWidget *parent) : QWidget(parent)
{
    this->simulator = simulator;

    this->setAutoFillBackground(true);

    layout = std::shared_ptr<QVBoxLayout>(new QVBoxLayout(this));
    layout->setMargin(2);
    layout->setSpacing(0);

    titleLayout = std::shared_ptr<QGridLayout>(new QGridLayout);
    comboTitle = std::shared_ptr<QComboBox>(new QComboBox);

    for (unsigned i = 0; i < pagesNumber; i++)
    {
        comboTitle->addItem(QString("Page %1: [0x%2 - 0x%3]")
                            .arg(QString::number(i))
                            .arg(QString::number(bytesPerPage * i, 16))
                            .arg(QString::number(bytesPerPage * (i + 1) - 1, 16)));
    }

    titleLayout->addWidget(comboTitle.get(), 0, 0, Qt::AlignCenter);

    mainLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout);

    scroll = std::shared_ptr<QScrollBar>(new QScrollBar);

    memoryGB = std::shared_ptr<QGroupBox>(new QGroupBox);
    memLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(memoryGB.get()));

    memory = std::shared_ptr<MemoryTable>(new MemoryTable(columnsNumber, pagesNumber, bytesPerPage));
    memLayout->addWidget(memory.get());

    for (unsigned j = 0; j < pagesNumber; j++)
    {
        QGroupBox* ioGB = new QGroupBox("I/O " + QString::number(j));   /// TODO delete this pointer
        ioGB->setMinimumWidth(65);

        QVBoxLayout* ioLayout = new QVBoxLayout(ioGB);  /// TODO delete this pointer

        for(unsigned i=0; i < ioPerPage; i++)
        {
            QCheckBox* ioCB = new QCheckBox();  /// TODO delete this pointer
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

        if (j == 0)
        {
            activeIOGroupBox = ioGB;
        }
        else
        {
            ioGB->setVisible(false);
        }
    }

    scroll->setMinimum(0);
    scroll->setMaximum(pagesNumber * bytesPerPage - 1);
    this->setMemoryTitle(0);

    mainLayout->addWidget(memoryGB.get());
    mainLayout->addWidget(scroll.get());

    layout->addLayout(titleLayout.get());
    layout->addLayout(mainLayout.get());

    // connects
    connect(scroll.get(), &QScrollBar::valueChanged,
        [=](int value)
        {
            memory->setSelectedCell(value);

            this->setMemoryTitle(value);

            this->setIOGroupBoxVisible(value / bytesPerPage);
        });

    connect(memory.get(), &QTableWidget::itemSelectionChanged,
        [=]()
        {
            int row = memory->currentRow();
            int column = memory->currentColumn();

            scroll->setValue(row * columnsNumber + column);

            this->setMemoryTitle(row * columnsNumber + column);

            this->setIOGroupBoxVisible((row * columnsNumber) / bytesPerPage);
        });

    connect(comboTitle.get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index)
        {
            scroll->setValue(index * bytesPerPage - columnsNumber);

            memory->setSelectedCell(index * bytesPerPage);

            this->setIOGroupBoxVisible(index);
        });

    // ROM
    ROM* rom = simulator->getRom().get();
    connect(rom, SIGNAL(onRomCleared()), this, SLOT(handleRomCleared()));

    connect(rom, SIGNAL(onRomChanged(uint,uint)), this, SLOT(handleRomChanged(uint,uint)));

    connect(rom, SIGNAL(onRomIOChanged(uint,uint)), this, SLOT(handleRomIOChanged(uint,uint)));
}

RomWidget::~RomWidget()
{
    for (QCheckBox* io : ios)
    {
        delete(io);
    }
}

void RomWidget::setMemoryTitle(int value)
{
    comboTitle->setCurrentIndex(value / bytesPerPage);
}

void RomWidget::setIOGroupBoxVisible(int value)
{
    QGroupBox* gb = (QGroupBox*)memLayout->itemAt(value + 1)->widget();
    activeIOGroupBox->setVisible(false);
    gb->setVisible(true);
    activeIOGroupBox = gb;
}

void RomWidget::setIO(unsigned page, unsigned value)
{
    if (page > pagesNumber)
    {
        std::cerr << "RomWidget: setIO: Wrong page: " << page << std::endl;
        return; /// TODO make an exception
    }

    if (value > (pow(2, ioPerPage) - 1))    // 4 bits number
    {
        std::cerr << "RomWidget: setIO: Wrong value: " << value << std::endl;
        return; /// TODO make an exception
    }

    for (unsigned i = 0; i < ioPerPage; i++)
    {
        QCheckBox* io = ios.at(page * ioPerPage + i);
        io->setChecked((value & (unsigned)pow(2, i)) >> i);
    }
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

            QTableWidgetItem* w = new QTableWidgetItem(t);  /// TODO delete this pointer
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
        (lowByte <= 0xF) ? t.append("0") : t.append("");
        t.append(QString::number(lowByte, 16));
        QTableWidgetItem* w = new QTableWidgetItem(t);  /// TODO delete this pointer
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

void RomWidget::handleRomCleared()
{
    memory->clear();
}

void RomWidget::handleRomChanged(unsigned addr, unsigned value)
{
    memory->setValue(addr, value);
}

void RomWidget::handleRomIOChanged(unsigned page, unsigned value)
{
    this->setIO(page, value);
}

void RomWidget::wheelEvent(QWheelEvent *event)
{
    int p = event->delta() / 120; // +1 when scroll up, -1 when down
    int newValue = scroll->value() - p;

    scroll->setValue(newValue);
}
