#include "led.h"

Led::Led(QWidget *parent) : QWidget(parent)
{
    ledImage = std::shared_ptr<LedImage>(new LedImage);
    coloredComboBox = std::shared_ptr<ColoredComboBox>(new ColoredComboBox);
    connector = std::shared_ptr<ChooseIOWidget>(new ChooseIOWidget);

    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));
    layout->addWidget(coloredComboBox.get(), 0,0);
    layout->addWidget(ledImage.get(), 1,0);
    layout->addWidget(connector.get(), 2,0);

    ledImage->light(true);

    connect(coloredComboBox.get(),SIGNAL(activated(QString)), this, SLOT(coloredComboboxChanged(QString)));
//    connect(connector.get(),SIGNAL(change...), this, SLOT(...do something on changed));
}

void Led::coloredComboboxChanged(QString color)
{
    ledImage->setColor(color);
}
