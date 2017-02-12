#include "iowidgetn.h"

// TODO change numbers to constants !!!
// TODO Change pictures of LED, because leds on that pictures have got different positions
// TODO Remove the legs on LED, they are too long or join them to ground or power and show this on the pictures
IOWidgetN::IOWidgetN() : QWidget()
{
    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));

    for (int i = 0; i < 8; i++)
    {
        LED* led = new LED(LED::Color::BLUE);
        ColoredComboBox* comboBoxColored = new ColoredComboBox(led);
        ChooseIOWidget* chooseIO = new ChooseIOWidget;

        connect(comboBoxColored, SIGNAL(activated(QString)), this, SLOT(changeLedColor(QString)));
        connect(led, SIGNAL(changed()), this, SLOT(update()));

        comboBoxes.push_back(comboBoxColored);
        leds.push_back(led);
        chooseIOs.push_back(chooseIO);

        led->setScale(0.5);
        led->setTurnOn(true);

        layout->addWidget(comboBoxColored, 0, i);
        layout->addWidget(led, 1, i);
        layout->addWidget(chooseIO, 2, i);
    }
}

IOWidgetN::~IOWidgetN()
{
    // delete here something

    for (ColoredComboBox* comboBox : comboBoxes)
    {
        delete (comboBox);
    }

    for (LED* led : leds)
    {
        delete (led);
    }

    for (ChooseIOWidget* chooseIO : chooseIOs)
    {
        delete (chooseIO);
    }
}

void IOWidgetN::update()
{
    for (LED* led : leds)
    {
        led->update();
    }
}

void IOWidgetN::changeLedColor(QString color)
{
    ((ColoredComboBox*)QObject::sender())->getLed()->setColor(color);
}
