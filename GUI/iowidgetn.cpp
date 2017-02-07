#include "iowidgetn.h"

IOWidgetN::IOWidgetN() : QWidget()
{
    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));

    led0 = std::shared_ptr<LED>(new LED(LED::Color::BLUE));
    layout->addWidget(led0.get(), 1, 0);

    cbColored = std::shared_ptr<ColoredComboBox>(new ColoredComboBox);
    layout->addWidget(cbColored.get(), 0, 0);

    connect(cbColored.get(), SIGNAL(activated(QString)), this, SLOT(changeLedColor(QString)));
    connect(led0.get(), SIGNAL(changed()), this, SLOT(update()));


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
