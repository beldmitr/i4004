#include "stackwidget.h"

StackWidget::StackWidget(QWidget *parent) : QGroupBox(parent)
{
    this->setTitle("Stack");

    layout = new QGridLayout(this);

    lblPC = new QLabel("PC");
    lblLevel1 = new QLabel("level 1");
    lblLevel2 = new QLabel("level 2");
    lblLevel3 = new QLabel("level 3");

    edtPC = new QTextEdit();
    edtLevel1 = new QTextEdit();
    edtLevel2 = new QTextEdit();
    edtLevel3 = new QTextEdit();

    edtPC->setReadOnly(true);
    edtLevel1->setReadOnly(true);
    edtLevel2->setReadOnly(true);
    edtLevel3->setReadOnly(true);

    edtPC->setText("0");
    edtLevel1->setText("0");
    edtLevel2->setText("0");
    edtLevel3->setText("0");

    layout->addWidget(lblPC, 0, 0);
    layout->addWidget(lblLevel1, 1, 0);
    layout->addWidget(lblLevel2, 2, 0);
    layout->addWidget(lblLevel3, 3, 0);

    layout->addWidget(edtPC, 0, 1);
    layout->addWidget(edtLevel1, 1, 1);
    layout->addWidget(edtLevel2, 2, 1);
    layout->addWidget(edtLevel3, 3, 1);

    this->setLayout(layout);
}

StackWidget::~StackWidget()
{
    delete(layout);

    delete(lblPC);
    delete(lblLevel1);
    delete(lblLevel2);
    delete(lblLevel3);

    delete(edtPC);
    delete(edtLevel1);
    delete(edtLevel2);
    delete(edtLevel3);
}
