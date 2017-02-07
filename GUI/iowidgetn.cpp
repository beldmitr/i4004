#include "iowidgetn.h"

IOWidgetN::IOWidgetN() : QWidget()
{
    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));

    led0 = std::shared_ptr<LED>(new LED(LED::Color::RED));
    layout->addWidget(led0.get(), 0, 0);

    ColoredComboBox* cbColored = new ColoredComboBox;
    layout->addWidget(cbColored, 0, 1);

    connect(led0.get(), SIGNAL(changed()), this, SLOT(update()));
}

IOWidgetN::~IOWidgetN()
{
    // delete here something
}

void IOWidgetN::update()
{
    led0->update();
}
