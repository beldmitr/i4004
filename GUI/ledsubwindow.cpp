#include "ledsubwindow.h"

LEDSubWindow::LEDSubWindow() : SubWindow()
{
    ledPanel = std::shared_ptr<LEDPanel>(new LEDPanel);
    this->setWidget(ledPanel.get());
}

LEDSubWindow::~LEDSubWindow()
{

}
