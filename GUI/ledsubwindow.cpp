#include "ledsubwindow.h"

LEDSubWindow::LEDSubWindow(Simulator *simulator) : SubWindow()
{
    this->simulator = simulator;

    this->setWindowTitle("LED panel");
    this->setWindowIcon(QIcon(":/Resources/icons/led.png"));

    centralWidget = std::shared_ptr<QWidget>(new QWidget);
    layout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(centralWidget.get()));
    layout->setMargin(10);
    layout->setSpacing(0);

    this->setWidget(centralWidget.get());

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

void LEDSubWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange)
    {
        QWindowStateChangeEvent* ev = static_cast<QWindowStateChangeEvent*>(event);
        if (!(ev->oldState() & Qt::WindowMaximized) && windowState() & Qt::WindowMaximized)
        {
            this->setWindowState(Qt::WindowNoState);
        }
        else
        {
            QMdiSubWindow::changeEvent(event);
        }
    }
}
