#include "led.h"

LED::LED(LED::Color color) : QImage()
{
    this->color = color;
    this->isOn = false;

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

    this->load(filenameOn);

    this->filenameOff = ":/Resources/components/LedWhite.png";
}

LED::~LED()
{
    // delete here something
}

void LED::on()
{
    this->isOn = true;
    this->load(filenameOn);
}

void LED::off()
{
    this->isOn = true;
    this->load(filenameOff);
}

LED::Color LED::getColor() const
{
    return color;
}

bool LED::getIsOn() const
{
    return isOn;
}
