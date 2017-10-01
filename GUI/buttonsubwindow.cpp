#include "buttonsubwindow.h"

ButtonSubWindow::ButtonSubWindow(Simulator* simulator) : SubWindow()
{
    this->setWindowTitle("Button panel");
    this->setWindowIcon(QIcon(":/Resources/icons/button.png"));

    centralWidget = std::shared_ptr<QWidget>(new QWidget);
    this->setWidget(centralWidget.get());

    layout = std::shared_ptr<QGridLayout>(new QGridLayout(centralWidget.get()));
    layout->setMargin(0);
    layout->setSpacing(0);

    for (int i = 0; i < 8; i++)
    {
        ChooseIOWidget* chooseIO = new ChooseIOWidget;
        Button* button = new Button(simulator, chooseIO);

        layout->addWidget(button, 0, i, Qt::AlignCenter);
        layout->addWidget(chooseIO, 1, i);

        buttons.push_back(button);
        connectors.push_back(chooseIO);
    }
}

ButtonSubWindow::~ButtonSubWindow()
{
    for (Button* b : buttons)
    {
        delete (b);
    }

    for (ChooseIOWidget* c : connectors)
    {
        delete (c);
    }
}
