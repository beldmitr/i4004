#include "debuggerlist.h"

DebuggerList::DebuggerList(Compiler* compiler) : QTableWidget()
{
    this->compiler = compiler;

    this->setColumnCount(columnNumbers);

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->horizontalHeader()->setStretchLastSection(true);
    this->setHorizontalHeaderLabels(QStringList() << tr("Code") << tr("Command"));

    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    this->setMinimumWidth(300);

    // Compiler
    connect(this->compiler, &Compiler::onCompiled, [=](){
        std::vector<unsigned> code = this->compiler->getObjectCode();
        this->setCode(code);
    });
}

DebuggerList::~DebuggerList()
{
    for (QTableWidgetItem* i : items)
    {
        delete i;
    }
}

void DebuggerList::setCode(std::vector<unsigned> code)
{
    this->setRowCount(0);

    for (unsigned i = 0; i < code.size(); i++)
    {
        unsigned byte = code[i];
        unsigned command = byte;
        bool longCommand = Debugger::hasNextByte(byte);
        if (longCommand)
        {
            int low = code[++i];  // read the next byte
            command = (byte << 8) | low;   // combine code to 2 byte
        }

        this->insertRow(this->rowCount());


        QTableWidgetItem* codeItem = new QTableWidgetItem(QString::number(command, 16));
        codeItem->setTextAlignment(Qt::AlignCenter);
        codeItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(this->rowCount()-1, 0, codeItem);
//        items.push_back(codeItem);    // DON'T DO THIS. IT WILL CAUSE A CRASH. this->setRowCount(0); already removes items !!!

        QTableWidgetItem* commandItem = new QTableWidgetItem(Debugger::codeToInstruction(command));
        commandItem->setTextAlignment(Qt::AlignCenter);
        commandItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(this->rowCount()-1, 1, commandItem);
//        items.push_back(commandItem); // DON'T DO THIS. IT WILL CAUSE A CRASH. this->setRowCount(0); already removes items !!!
    }

    this->viewport()->update();

}
