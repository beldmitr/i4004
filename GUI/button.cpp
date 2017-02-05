#include "button.h"

Button::Button() : QPushButton()
{
    this->setStyleSheet("border-image:url(:/Resources/components/button.png)");
//    this->setAutoFillBackground(true);
//    this->setIcon(QIcon(":/Resources/components/button.png"));
//    this->setIconSize(QSize(40,40));

}

Button::~Button()
{
    // delete here something
}
