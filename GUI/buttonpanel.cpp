#include "buttonpanel.h"

/// TODO delete pointers
ButtonPanel::ButtonPanel(QWidget *parent) : QWidget(parent)
{
    layout = std::shared_ptr<QGridLayout>(new QGridLayout(this));
    this->setLayout(layout.get());

    for (int i = 0; i < 8; i++)
    {
        Button* button = new Button;    /// TODO what about deleting these pointers or make them smart
        ChooseIOWidget* chooseIO = new ChooseIOWidget;

        layout->addWidget(button, 0, i);
        layout->addWidget(chooseIO, 1, i);
    }
}

ButtonPanel::~ButtonPanel()
{
    // delete here something or finalize
}
