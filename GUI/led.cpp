#include "led.h"

void LED::update()
{
    this->setPixmap(QPixmap::fromImage(image));
}

LED::LED(LED::Color color) : QLabel()
{
    this->setAutoFillBackground(true);

    this->color = color;
    this->isOn = false;
    this->filenameOff = ":/Resources/components/LedWhite.png";

    setColor(color);

    setTurnOn(isOn);
}

LED::~LED()
{
    // delete here something
}

void LED::setColor(LED::Color color)
{
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

    image.load(filenameOn);

    update();
}

void LED::setTurnOn(bool light)
{
    if (light)
    {
        this->isOn = true;
        image.load(filenameOn);
    }
    else
    {
        this->isOn = true;
        image.load(filenameOff);
    }

    update();
}

void LED::scaled(double scale)
{
    QSize size = image.size();

    image = image.scaled(size * scale, Qt::KeepAspectRatio);

    this->setPixmap(QPixmap::fromImage(image));
}

LED::Color LED::getColor() const
{
    return color;
}

bool LED::getIsOn() const
{
    return isOn;
}
