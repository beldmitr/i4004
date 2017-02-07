#include "led.h"

LED::LED(LED::Color color) : QLabel()
{
    this->setAutoFillBackground(true);

    this->color = color;
    this->isOn = false;
    this->scale = 1.0;
    this->filenameOff = ":/Resources/components/LedWhite.png";

    // Factly this method draws the element
    update();
}

LED::~LED()
{
    // delete here something
}

void LED::update()
{
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

    // draw the image
    this->setPixmap(QPixmap::fromImage(image));
}

void LED::setColor(LED::Color color)
{
    this->color = color;

    emit changed(); // send event
}

void LED::setColor(QString color)
{
    if (color == "Red")
    {
        filenameOn = ":/Resources/components/LedRed.png";
        this->color = LED::Color::RED;
    } else if (color == "Orange")
    {
        filenameOn = ":/Resources/components/LedOrange.png";
        this->color = LED::Color::ORANGE;
    } else if (color == "Yellow")
    {
        filenameOn = ":/Resources/components/LedYellow.png";
        this->color = LED::Color::YELLOW;
    } else if (color == "Green")
    {
        filenameOn = ":/Resources/components/LedGreen.png";
        this->color = LED::Color::GREEN;
    } else if (color == "Blue")
    {
        filenameOn = ":/Resources/components/LedBlue.png";
        this->color = LED::Color::BLUE;
    } else if (color == "Pink")
    {
        filenameOn = ":/Resources/components/LedPink.png";
        this->color = LED::Color::PINK;
    } else
    {
        filenameOn = ":/Resources/components/LedWhite.png";
        this->color = LED::Color::NONE;
    }

    emit changed(); // send event
}

void LED::setTurnOn(bool light)
{
    this->isOn = light;

    emit changed(); // send event
}

void LED::setScale(double scale)
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
