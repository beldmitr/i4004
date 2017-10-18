#include "debuggerlist.h"

DebuggerList::DebuggerList(Compiler* compiler) : QTableWidget()
{
    this->compiler = compiler;

    this->setColumnCount(columnNumbers);

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->horizontalHeader()->setStretchLastSection(true);
    this->setHorizontalHeaderLabels(QStringList() << "" << tr("Address") << tr("Code") << tr("Command"));

    // Don't delete headerView pointer. I didn't create it with "new"
    QHeaderView* headerView = this->horizontalHeader();
    headerView->resizeSection(0, 26);

    connect(headerView, &QHeaderView::sectionClicked, [=](int index) {
        if (index == 0)
        {
            /// TODO delete all breakpoints
        }
    });

    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSelectionMode(QAbstractItemView::NoSelection);

    this->verticalHeader()->setVisible(false);

    this->setMinimumWidth(350);

    /// TODO make 00 | NOP everywhere by default from the beggining


    connect(this, &QTableWidget::cellClicked, [=](int row, int /*col*/){

        QTableWidgetItem* addressItem = this->item(row, 1);
        QString addrTxt = addressItem->text();
        unsigned addr = addrTxt.toUInt(nullptr, 16);

        QTableWidgetItem* breakpointItem = this->item(row, 0);
        QIcon icon = breakpointItem->icon();
        if (icon.isNull())
        {
            breakpointItem->setIcon(QIcon(":/Resources/icons/breakpoint.png"));
            Debugger::addBreakpoint(addr);
        }
        else
        {
            breakpointItem->setIcon(QIcon());
            Debugger::removeBreakpoint(addr);
        }
    });

    // Compiler
    connect(this->compiler, &Compiler::onCompiled, [=](){
        std::vector<unsigned> code = this->compiler->getObjectCode();
        this->setCode(code);
        Debugger::clearBreakpoint();
    });
}

DebuggerList::~DebuggerList()
{
    for (QTableWidgetItem* i : items)
    {
        delete i;
    }
}

void DebuggerList::selectAddress(unsigned address)
{

}

void DebuggerList::deselectAll()
{

}

void DebuggerList::setCode(std::vector<unsigned> code)
{
    this->setRowCount(0);

    unsigned addr = 0;

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

        QTableWidgetItem* brkptItem = new QTableWidgetItem();
        brkptItem->setTextAlignment(Qt::AlignCenter);
        brkptItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(this->rowCount()-1, 0, brkptItem);
//        items.push_back(brkptItem);    // DON'T DO THIS. IT WILL CAUSE A CRASH. this->setRowCount(0); already removes items !!!

        QTableWidgetItem* addrItem = new QTableWidgetItem(Debugger::addressToString(addr));
        addrItem->setTextAlignment(Qt::AlignCenter);
        addrItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(this->rowCount()-1, 1, addrItem);
//        items.push_back(addrItem);    // DON'T DO THIS. IT WILL CAUSE A CRASH. this->setRowCount(0); already removes items !!!

        QTableWidgetItem* codeItem = new QTableWidgetItem(Debugger::commandToString(command));
        codeItem->setTextAlignment(Qt::AlignCenter);
        codeItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(this->rowCount()-1, 2, codeItem);
//        items.push_back(codeItem);    // DON'T DO THIS. IT WILL CAUSE A CRASH. this->setRowCount(0); already removes items !!!

        QTableWidgetItem* commandItem = new QTableWidgetItem(Debugger::codeToInstruction(command));
        commandItem->setTextAlignment(Qt::AlignCenter);
        commandItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(this->rowCount()-1, 3, commandItem);
//        items.push_back(commandItem); // DON'T DO THIS. IT WILL CAUSE A CRASH. this->setRowCount(0); already removes items !!!

        if (longCommand)
        {
            addr += 2;
        }
        else
        {
            addr += 1;
        }
    }

    this->viewport()->update();

}

