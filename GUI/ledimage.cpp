#include "ledimage.h"

LedImage::LedImage(QWidget *parent) : QLabel(parent)
{
    this->setMargin(0);
    this->setMaximumWidth(50);

    pics =
    {
        {"Blue", QImage(":/Resources/components/LedBlue.png")},
        {"Green", QImage(":/Resources/components/LedGreen.png")},
        {"Orange", QImage(":/Resources/components/LedOrange.png")},
        {"Red", QImage(":/Resources/components/LedRed.png")},
        {"Pink", QImage(":/Resources/components/LedPink.png")},
        {"White", QImage(":/Resources/components/LedWhite.png")},
        {"Yellow", QImage(":/Resources/components/LedYellow.png")}
    };

    this->setAlignment(Qt::AlignCenter);
    this->setAutoFillBackground(true);

    image_on = pics.find("Red")->second;
    image_off = pics.find("White")->second;

    isLight = false;

    paint();
}

LedImage::~LedImage()
{

}

void LedImage::light(bool isLight)
{
    if (this->isLight != isLight)
    {
        this->isLight = isLight;
        paint();
    }
}

void LedImage::setColor(QString color)
{
    auto it = pics.find(color);
    if (it != pics.end())
    {
        image_on = it->second;
        paint();
    }
}

void LedImage::paint()
{
    QImage image = isLight ? image_on : image_off;
    this->setPixmap(QPixmap::fromImage(image));
}




