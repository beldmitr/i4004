#include "sevensegmentsubwindow.h"

SevenSegmentSubWindow::SevenSegmentSubWindow() : SubWindow()
{
    sevenSegmentPanel = std::shared_ptr<SevenSegmentPanel>(new SevenSegmentPanel);
    this->setWidget(sevenSegmentPanel.get());

    this->setWindowTitle("Seven segment panel");
    this->setWindowIcon(QIcon(":/Resources/icons/SevenSegment.png"));

    //Changing size of the window, when the number of 7segments were changed
    connect(sevenSegmentPanel.get(), &SevenSegmentPanel::changedSegmentCount, [=]() {
        if (!this->isMaximized())
        {
            this->adjustSize();
        }
    });

    connect(this, &SubWindow::windowStateChanged, [=]() {
        if (!this->isMaximized() && !this->isMinimized())
        {
            this->adjustSize();
        }
    });
    //*******************************************************************************
}

SevenSegmentSubWindow::~SevenSegmentSubWindow()
{

}
