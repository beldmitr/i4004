#include "buttonpanel.h"

ButtonPanel::ButtonPanel(QWidget *parent) : QWidget(parent)
{
    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));
    this->setLayout(layout.get());

    for (int i = 0; i < 8; i++)
    {
        Button* button = new Button;
        ChooseIOWidget* chooseIO = new ChooseIOWidget;

        layout->addWidget(button, 0, i);
        layout->addWidget(chooseIO, 1, i);
    }

    this->setWindowTitle("Button panel");
    this->setWindowIcon(QIcon(":/Resources/icons/button.png"));
}

ButtonPanel::~ButtonPanel()
{
    // delete here something or finalize
}