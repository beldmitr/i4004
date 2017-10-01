#include "ledsubwindow.h"

LEDSubWindow::LEDSubWindow(Simulator *simulator) : SubWindow()
{
    this->simulator = simulator;

    this->setWindowTitle("LED panel");
    this->setWindowIcon(QIcon(":/Resources/icons/led.png"));

    centralWidget = std::shared_ptr<QWidget>(new QWidget);
    layout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(centralWidget.get()));
    layout->setMargin(0);
    layout->setSpacing(0);

    this->setWidget(centralWidget.get());
//    this->setStyleSheet(this->styleSheet() + " border: 1px solid black");


    for (int i = 0; i < 8; i++)
    {
        Led* led = new Led(simulator);
        layout->addWidget(led);
        leds.push_back(led);
    }

}

LEDSubWindow::~LEDSubWindow()
{
    for (Led* led : leds)
    {
        delete (led);
    }
}
