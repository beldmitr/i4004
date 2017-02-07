#include "iowidgetn.h"

IOWidgetN::IOWidgetN() : QWidget()
{
    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));

    led0 = std::shared_ptr<LED>(new LED(LED::Color::RED));

    connect(led0.get(), SIGNAL(changed()), this, SLOT(update()));

    led0->scaled(0.25);

    layout->addWidget(led0.get(), 0, 0);

    led0->setColor(LED::Color::GREEN);

    led0->setTurnOn();

    led0->setColor(LED::Color::ORANGE);




//    led0->setTurnOn(true);
//    led0->setTurnOn();

}

IOWidgetN::~IOWidgetN()
{
    // delete here something
}

void IOWidgetN::update()
{
    led0->update();
}
