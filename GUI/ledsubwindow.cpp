#include "ledsubwindow.h"

LEDSubWindow::LEDSubWindow() : SubWindow()
{
    ledPanel = std::shared_ptr<LEDPanel>(new LEDPanel);
    this->setWidget(ledPanel.get());
    this->setWindowTitle("Input/Output");
    this->setWindowIcon(QIcon(":/Resources/icons/io.png"));
}

LEDSubWindow::~LEDSubWindow()
{

}
