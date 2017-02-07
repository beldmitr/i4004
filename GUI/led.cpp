#include "led.h"

LED::LED(LED::Color color) : QLabel()
{
    this->setAutoFillBackground(true);

    this->color = color;
    this->isOn = false;
    this->scale = 1.0;
    this->filenameOff = ":/Resources/components/LedWhite.png";

    emit changed(); // send event
}

LED::~LED()
{
    // delete here something
}

void LED::update()
{
    std::cout << "update" << std::endl;
    // update color
    switch(color)
    {
        case Color::NONE:
            filenameOn = ":/Resources/components/LedWhite.png";
            break;
        case Color::RED:
            filenameOn = ":/Resources/components/LedRed.png";
            break;
        case Color::ORANGE:
            filenameOn = ":/Resources/components/LedOrange.png";
            break;
        case Color::YELLOW:
            filenameOn = ":/Resources/components/LedYellow.png";
            break;
        case Color::GREEN:
            filenameOn = ":/Resources/components/LedGreen.png";
            break;
        case Color::BLUE:
            filenameOn = ":/Resources/components/LedBlue.png";
            break;
        case Color::PINK:
            filenameOn = ":/Resources/components/LedPink.png";
            break;
    }

    // update turnOn
    if (isOn)
    {
        image.load(filenameOn);
    }
    else
    {
        image.load(filenameOff);
    }

    // update scale
    QSize size = image.size();

    image = image.scaled(size * scale, Qt::KeepAspectRatio);

    // redraw
    this->setPixmap(QPixmap::fromImage(image));
}

void LED::setColor(LED::Color color)
{
    this->color = color;

    emit changed(); // send event
}

void LED::setTurnOn(bool light)
{
    this->isOn = light;

    emit changed(); // send event
}

void LED::scaled(double scale)
{
    this->scale = scale;

    emit changed(); // send event
}

LED::Color LED::getColor() const
{
    return color;
}

bool LED::getIsOn() const
{
    return isOn;
}
