#include "chooseiowidget.h"

/// TODO delete pointers
/**
 * TODO make more universal widget:
 *   1. setROMEnabled
 *   2. setDRAMEnabled
 *   3. Hint to status menu
*/
ChooseIOWidget::ChooseIOWidget(QWidget *parent) : QWidget(parent)
{
    this->setMinimumWidth(135);

    layout = std::shared_ptr<QVBoxLayout>(new QVBoxLayout(this));

    button = std::shared_ptr<QPushButton>(new QPushButton("N/C"));
    button->setToolTip("No connection");

    layout->addWidget(button.get());
    layout->setMargin(0);

    menuButton = std::shared_ptr<QMenu>(new QMenu(button.get()));

    QActionGroup* groupAction = new QActionGroup(menuButton.get());

    QMenu* menuROM = new QMenu("ROM");
    QMenu* menuDRAM = new QMenu("Data RAM");
    QAction* actionNoConnection = new QAction("No connection");
    connect(actionNoConnection, &QAction::triggered,
            [=]()
    {
        this->button->setText("N/C");
        this->button->setToolTip("No connection");

        emit onDisconnected();
    });

    actionNoConnection->setActionGroup(groupAction);
    actionNoConnection->setCheckable(true);
    actionNoConnection->setChecked(true);

    menuButton->addMenu(menuROM);
    menuButton->addMenu(menuDRAM);
    menuButton->addAction(actionNoConnection);

    for (int i = 0; i < 16; i++)
    {
        QMenu* pageMenu = new QMenu("Page " + QString::number(i));
        menuROM->addMenu(pageMenu);
        for (int j = 0; j < 4; j++)
        {
            QAction* bitAction = new QAction("Bit " + QString::number(j));
            bitAction->setCheckable(true);
            bitAction->setActionGroup(groupAction);
            pageMenu->addAction(bitAction);

            connect(bitAction, &QAction::triggered,
                    [=]()
            {
                this->button->setText("ROM:P" + QString::number(i) + ",b" + QString::number(j));
                this->button->setToolTip("ROM: Page " + QString::number(i) + ", bit " + QString::number(j));

                emit onROMConnected(i, j);
            });
        }
    }

    for (int i = 0; i < 8; i++) // 8 banks
    {
        QMenu* bankMenu = new QMenu("Bank " + QString::number(i));
        menuDRAM->addMenu(bankMenu);
        for (int j = 0; j < 4; j++) // 4 chips at each bank
        {
            QMenu* chipMenu = new QMenu("Chip " + QString::number(j));
            bankMenu->addMenu(chipMenu);
            for (int k = 0; k < 4; k++) // 4 bits IO at each chip
            {
                QAction* bitAction = new QAction("Bit " + QString::number(k));
                bitAction->setCheckable(true);
                bitAction->setActionGroup(groupAction);
                chipMenu->addAction(bitAction);

                connect(bitAction, &QAction::triggered,
                        [=]()
                {
                    this->button->setText("DR:B" + QString::number(i) + ",C"
                                    + QString::number(j) + ",b" + QString::number(k));
                    this->button->setToolTip("Data RAM: Bank " + QString::number(i) + ", Chip "
                                             + QString::number(j) + ", bit " + QString::number(k));
                    emit onDRAMConnected(i, j, k);
                });
            }
        }
    }

    button->setMenu(menuButton.get());
}

ChooseIOWidget::~ChooseIOWidget()
{
    // delete here something
}
