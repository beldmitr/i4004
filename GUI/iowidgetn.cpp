#include "iowidgetn.h"

IOWidgetN::IOWidgetN() : QWidget()
{
    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));

    led0 = std::shared_ptr<LED>(new LED(LED::Color::BLUE));
    layout->addWidget(led0.get(), 1, 0);

    ColoredComboBox* cbColored = new ColoredComboBox;
    layout->addWidget(cbColored, 0, 0);

    connect(led0.get(), SIGNAL(changed()), this, SLOT(update()));
    connect(cbColored, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeLedColor(QString)));

    led0->setScale(0.25);
    led0->setTurnOn(true);
}

IOWidgetN::~IOWidgetN()
{
    // delete here something
}

void IOWidgetN::update()
{
    led0->update();
}

void IOWidgetN::changeLedColor(QString color)
{
    led0->setColor(color);
}
