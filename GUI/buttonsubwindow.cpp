#include "buttonsubwindow.h"

ButtonSubWindow::ButtonSubWindow(Simulator* simulator) : SubWindow()
{
    this->setWindowTitle("Button panel");
    this->setWindowIcon(QIcon(":/Resources/icons/button.png"));

    centralWidget = std::shared_ptr<QWidget>(new QWidget);
    this->setWidget(centralWidget.get());

    layout = std::shared_ptr<QGridLayout>(new QGridLayout(centralWidget.get()));
    layout->setMargin(10);
    layout->setSpacing(10);

    for (unsigned i = 0; i < buttonNumber; i++)
    {
        ChooseIOWidget* chooseIO = new ChooseIOWidget(false);
        Button* button = new Button(simulator, chooseIO);

        unsigned buttonRows = buttonNumber / buttonColumns;

        unsigned buttonRow = (i / buttonColumns) * buttonRows;
        unsigned chooserRow = (i / buttonColumns) * buttonRows + 1;

        layout->addWidget(button, buttonRow, i % buttonColumns, Qt::AlignCenter);
        layout->addWidget(chooseIO, chooserRow, i % buttonColumns, Qt::AlignCenter);

        buttons.push_back(button);
        connectors.push_back(chooseIO);

        chooseIO->setConnection(ChooseIOWidget::IOType::ROM_IO, 4 + i / 4, 3 - i % 4);
    }

//    QSizePolicy sp = this->sizePolicy();
//    sp.setHorizontalPolicy(QSizePolicy::Maximum);
//    sp.setVerticalPolicy(QSizePolicy::Maximum);
//    this->setSizePolicy(sp);

//    this->move(35, 35);

//    QString os = QSysInfo::kernelType();
//    if (os == "darwin")
//    {
//        this->move(1040, 350);
//    }
//    else
//    {
//        this->move(1200, 350);
//    }

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

void ButtonSubWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange)
    {
        QWindowStateChangeEvent* ev = static_cast<QWindowStateChangeEvent*>(event);
        if (!(ev->oldState() & Qt::WindowMaximized) && windowState() & Qt::WindowMaximized)
        {
            this->setWindowState(Qt::WindowNoState);
        }
        else
        {
            QMdiSubWindow::changeEvent(event);
        }
    }
}
