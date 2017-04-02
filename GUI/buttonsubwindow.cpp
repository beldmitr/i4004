#include "buttonsubwindow.h"

ButtonSubWindow::ButtonSubWindow() : SubWindow()
{
    buttonPanel = std::shared_ptr<ButtonPanel>(new ButtonPanel);
    this->setWidget(buttonPanel.get());
    this->setWindowTitle("Button panel");
    this->setWindowIcon(QIcon(":/Resources/icons/button.png"));
}
