#include "processorwidget.h"

ProcessorWidget::ProcessorWidget(QWidget *parent) : QTreeWidget(parent)
{

//    this->setSelectionBehavior(QAbstractItemView::SelectItems);
//    this->setColumnCount(2);


//    // Header settings
//    QHeaderView* header = this->header();
//    header->setSectionResizeMode(QHeaderView::Stretch);

//    QTreeWidgetItem* headerItem = this->headerItem();
//    headerItem->setText(0, "Name");
//    headerItem->setText(1, "Value");

//    // Accumulator
//    QTreeWidgetItem* accumItem = new QTreeWidgetItem(this);
//    accumItem->setText(0, "Accumulator");
//    QLabel* accumLabel = new QLabel("0x0");
//    this->setItemWidget(accumItem, 1, accumLabel);

//    // Carry
//    QTreeWidgetItem* carry = new QTreeWidgetItem(this);
//    carry->setText(0, "Carry");
//    this->setItemWidget(carry, 1, new QCheckBox());

//    // Test
//    QTreeWidgetItem* test = new QTreeWidgetItem(this);
//    test->setText(0, "Test");
//    this->setItemWidget(test, 1, new QCheckBox());

//    // Cycles
//    QTreeWidgetItem* cycles = new QTreeWidgetItem(this);
//    cycles->setText(0, "Cycles");
//    QLabel* accumCycle = new QLabel("0");
//    this->setItemWidget(cycles, 1, accumCycle);

//    // Current Operation
//    QTreeWidgetItem* currOper = new QTreeWidgetItem(this);
//    currOper->setText(0, "Operation");
//    QLabel* accumCurrOp = new QLabel();
//    this->setItemWidget(currOper, 1, accumCurrOp);

//    // Add Stack
//    QTreeWidgetItem* stack = new QTreeWidgetItem(this);
//    stack->setText(0, "Stack");

//    // Add register items
//    for (int i=0; i < 4; i++)
//    {
//        QTreeWidgetItem* item = new QTreeWidgetItem(stack);
//        if (i == 0)
//        {
//            item->setText(0, "PC");
//        }
//        else
//        {
//            item->setText(0, "Level " + QString::number(i));
//        }
//        QLabel* lbl = new QLabel("0x0");
//        this->setItemWidget(item, 1, lbl);

//        stack->addChild(item);
//    }

//    // Add Registers
//    QTreeWidgetItem* registers = new QTreeWidgetItem(this);
//    registers->setText(0, "Registers");

//    // Add register items
//    for (int i=0; i < 16; i++)
//    {
//        QTreeWidgetItem* item = new QTreeWidgetItem(registers);
//        QString preffix;
//        if (i < 10)
//        {
//            preffix.append("0");
//        }
//        item->setText(0, "R" + preffix + QString::number(i));

//        QLabel* lbl = new QLabel("0x0");
//        this->setItemWidget(item, 1, lbl);
//        registers->addChild(item);
//    }

//    // Add Pairs
//    QTreeWidgetItem* pairs = new QTreeWidgetItem(this);
//    pairs->setText(0, "Pairs");

//    // Add register items
//    for (int i=0; i < 8; i++)
//    {
//        QTreeWidgetItem* item = new QTreeWidgetItem(pairs);
//        QString preffix;
//        if (i < 10)
//        {
//            preffix.append("0");
//        }
//        item->setText(0, "P" + preffix + QString::number(i));

//        QLabel* lbl = new QLabel("0x0");
//        this->setItemWidget(item, 1, lbl);
//        pairs->addChild(item);
//    }

//    this->expandAll();
}
