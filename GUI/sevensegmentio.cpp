#include "sevensegmentio.h"

// TODO rename to SevenSegment
SevenSegmentIO::SevenSegmentIO(QWidget *parent) : QLabel(parent)
{
    this->setAlignment(Qt::AlignCenter);

    this->setAutoFillBackground(false);

    scaled = 0.15;

    image.load(":/Resources/components/SevenSegment.png");
    image = image.scaled(image.size() * scaled);

    imagePinHorizontalOn.load(":/Resources/components/SevenSegmentHorizontalOn.png");
    imagePinHorizontalOn = imagePinHorizontalOn.scaled(imagePinHorizontalOn.size() * scaled);
    imagePinHorizontalOff.load(":/Resources/components/SevenSegmentHorizontalOff.png");
    imagePinHorizontalOff = imagePinHorizontalOff.scaled(imagePinHorizontalOff.size() * scaled);

    imagePinVerticalOn.load(":/Resources/components/SevenSegmentVerticalOn.png");
    imagePinVerticalOn = imagePinVerticalOn.scaled(imagePinVerticalOn.size() * scaled);
    imagePinVerticalOff.load(":/Resources/components/SevenSegmentVerticalOff.png");
    imagePinVerticalOff = imagePinVerticalOff.scaled(imagePinVerticalOff.size() * scaled);

    imagePinPointOn.load(":/Resources/components/SevenSegmentPointOn.png");
    imagePinPointOn = imagePinPointOn.scaled(imagePinPointOn.size() * scaled);
    imagePinPointOff.load(":/Resources/components/SevenSegmentPointOff.png");
    imagePinPointOff = imagePinPointOff.scaled(imagePinPointOff.size() * scaled);

    mapPins[Pins::A] = { QPoint(588, 236), imagePinHorizontalOn, imagePinHorizontalOff };
    mapPins[Pins::B] = { QPoint(1200, 421), imagePinVerticalOn, imagePinVerticalOff };
    mapPins[Pins::C] = { QPoint(996, 1240), imagePinVerticalOn, imagePinVerticalOff };
    mapPins[Pins::D] = { QPoint(184, 1866), imagePinHorizontalOn, imagePinHorizontalOff };
    mapPins[Pins::E] = { QPoint(42, 1239), imagePinVerticalOn, imagePinVerticalOff };
    mapPins[Pins::F] = { QPoint(245, 422), imagePinVerticalOn, imagePinVerticalOff };
    mapPins[Pins::G] = { QPoint(386, 1049), imagePinHorizontalOn, imagePinHorizontalOff };
    mapPins[Pins::DP] = { QPoint(1350, 1926), imagePinPointOn, imagePinPointOff };

    init();

    this->setPixmap(QPixmap::fromImage(image));
}

SevenSegmentIO::~SevenSegmentIO()
{
    // delete here something
}

void SevenSegmentIO::setPin(SevenSegmentIO::Pins pin, bool isTurnOn)
{
    QPainter p(&image);
    if (isTurnOn)
    {
        p.drawImage(mapPins[pin].position * scaled, mapPins[pin].imageOn);
    }
    else
    {
        p.drawImage(mapPins[pin].position * scaled, mapPins[pin].imageOff);
    }

    this->setPixmap(QPixmap::fromImage(image));
}

void SevenSegmentIO::init()
{
    QPainter p(&image);
    p.drawImage(mapPins[Pins::A].position * scaled, mapPins[Pins::A].imageOff);
    p.drawImage(mapPins[Pins::B].position * scaled, mapPins[Pins::B].imageOff);
    p.drawImage(mapPins[Pins::C].position * scaled, mapPins[Pins::C].imageOff);
    p.drawImage(mapPins[Pins::D].position * scaled, mapPins[Pins::D].imageOff);
    p.drawImage(mapPins[Pins::E].position * scaled, mapPins[Pins::E].imageOff);
    p.drawImage(mapPins[Pins::F].position * scaled, mapPins[Pins::F].imageOff);
    p.drawImage(mapPins[Pins::G].position * scaled, mapPins[Pins::G].imageOff);
    p.drawImage(mapPins[Pins::DP].position * scaled, mapPins[Pins::DP].imageOff);
}

void SevenSegmentIO::mousePressEvent(QMouseEvent* event)
{
    emit clicked(event);
}
