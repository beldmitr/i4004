#include "button.h"

Button::Button() : QPushButton()
{
    this->setStyleSheet("border-image:url(:/Resources/components/button.png)");
    QRect rect = this->geometry();
    rect.setWidth(50);
    rect.setHeight(50);
    this->setGeometry(rect);
//    this->setAutoFillBackground(true);
//    this->setIcon(QIcon(":/Resources/components/button.png"));
//    this->setIconSize(QSize(40,40));

}

Button::~Button()
{
    // delete here something
}
