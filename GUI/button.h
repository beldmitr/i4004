#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

#include "Simulator/simulator.h"
#include "chooseiowidget.h"

class Button : public QPushButton
{
public:
    explicit Button(Simulator* simulator, ChooseIOWidget* connector);
    virtual ~Button();

private:
    Simulator* simulator;

    ChooseIOWidget::IOType type = ChooseIOWidget::IOType::NONE;

    unsigned bank;
    unsigned chip;
    unsigned page;
    unsigned bit;

};

#endif // BUTTON_H
