#include "ledsubwindow.h"

LEDSubWindow::LEDSubWindow() : SubWindow()
{
    this->setWindowTitle("LED panel");
    this->setWindowIcon(QIcon(":/Resources/icons/led.png"));

    centralWidget = std::shared_ptr<QWidget>(new QWidget);
    layout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(centralWidget.get()));
    this->setWidget(centralWidget.get());


    for (int i = 0; i < 8; i++)
    {
        LedN* led = new LedN();
        layout->addWidget(led);
        leds.push_back(led);
    }

}

LEDSubWindow::~LEDSubWindow()
{
    for (LedN* led : leds)
    {
        delete (led);
    }
}
