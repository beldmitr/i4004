#ifndef LED_H
#define LED_H


#include <QWidget>
#include <QGridLayout>
#include <QComboBox>

#include <memory>
#include <iostream>

#include "Simulator/simulator.h"
#include "ledimage.h"
#include "coloredcombobox.h"
#include "chooseiowidget.h"

class Led : public QWidget
{
    Q_OBJECT
private:
    Simulator* simulator;

    std::shared_ptr<LedImage> ledImage;
    std::shared_ptr<ColoredComboBox> coloredComboBox;
    std::shared_ptr<ChooseIOWidget> connector;

    std::shared_ptr<QGridLayout> layout;

    enum class IOType
    {
        NONE,
        ROM_IO,
        DRAM_IO
    };

    IOType type = IOType::NONE;

    unsigned bank;
    unsigned chip;
    unsigned page;
    unsigned bit;

    unsigned value;

public:
    explicit Led(Simulator* simulator, QWidget *parent = 0);
    virtual ~Led();

signals:

private slots:

};

#endif // LED_H
