#include "iowidgetn.h"

IOWidgetN::IOWidgetN() : QWidget()
{
    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));


    LED* led0 = new LED(LED::Color::RED);

    led0->scaled(0.5);

    layout->addWidget(led0, 0, 0);

    led0->setColor(LED::Color::GREEN);

    led0->setTurnOn(false);

//    led0->setTurnOn(true);
//    led0->setTurnOn();

}

IOWidgetN::~IOWidgetN()
{
    // delete here something
}
