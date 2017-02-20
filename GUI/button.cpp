#include "button.h"

Button::Button() : QPushButton()
{
    this->setAutoFillBackground(true);
    this->setIcon(QIcon(":/Resources/components/button.png"));
    this->setIconSize(QSize(80,80));
}

Button::~Button()
{
    // delete here something
}
