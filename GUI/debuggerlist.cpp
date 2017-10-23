#include "debuggerlist.h"


/// TODO next/prev breakpoint, list of breakpoints ???

DebuggerList::DebuggerList(Compiler* compiler, Simulator *simulator) : QTableWidget()
{
    this->compiler = compiler;
    this->simulator = simulator;

    this->setColumnCount(columnNumbers);

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->horizontalHeader()->setStretchLastSection(true);
    this->setHorizontalHeaderLabels(QStringList() << "" << tr("Address") << tr("Code") << tr("Command"));

    QTableWidgetItem* delBrkpnt = this->horizontalHeaderItem(0);
    delBrkpnt->setIcon(QIcon(":/Resources/icons/removeBreakpoint.png"));
    delBrkpnt->setToolTip(tr("Remove all breakpoints"));

    // Don't delete headerView pointer. I didn't create it with "new"
    QHeaderView* headerView = this->horizontalHeader();
    headerView->resizeSection(0, 26);

    connect(headerView, &QHeaderView::sectionClicked, [=](int index) {
        if (index == 0)
        {
            for (int i = 0; i < this->verticalHeader()->count(); i++)
            {
                QTableWidgetItem* item = this->item(i, 0);
                item->setIcon(QIcon());
            }
            Debugger::clearBreakpoint();
        }
    });

    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSelectionMode(QAbstractItemView::NoSelection);

    this->verticalHeader()->setVisible(false);

    // Making minimal size according to screen resolution
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(desktop.primaryScreen());
    this->setMinimumHeight(rect.height() / 2);
    this->setMinimumWidth(350);

    connect(this, &QTableWidget::cellClicked, [=](int row, int /*col*/) {

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
    connect(this->compiler, &Compiler::onCompiled, [=]() {
        std::vector<unsigned> code = this->compiler->getObjectCode();
        this->setCode(code);
        this->selectAddress(0);
        Debugger::clearBreakpoint();
    });

    // Simulator
    connect(simulator, &Simulator::onStopPlaying, [=]() {
        unsigned addr = this->simulator->getCpu()->getPC();
        this->selectAddress(addr);
        this->viewport()->update();
    });

    connect(simulator, &Simulator::onStartPlaying, [=]() {
        this->deselectAll();
    });

    init();
}

DebuggerList::~DebuggerList()
{
//    for (QTableWidgetItem* item : items)
//    {
//        delete item;
//    }
}

void DebuggerList::selectAddress(unsigned addr)
{
    std::unordered_map<unsigned, unsigned>::const_iterator it = addrToRow.find(addr);
    if (it != addrToRow.end())
    {
        unsigned row = it->second;

        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->selectRow(row);
        this->setSelectionMode(QAbstractItemView::NoSelection);
    }
}

void DebuggerList::deselectAll()
{
    this->clearSelection();
}

void DebuggerList::setCode(std::vector<unsigned> code)
{
    addrToRow.clear();

    for (unsigned row = 0; row < rows; row++)
    {
        this->removeRow(row);
    }
    rows = 0;

    // This address will be shown in the table
    // It hides addresses for long commands
    // F.e. command FIM P0, 0x12 => 20 12, has got 2 bytes
    // But in the table we need to show it in one row:
    //  =============================================
    //  | addr |   code   |         command         |
    //  |--------------------------------------------
    //  |   0  |    ...   |           ...           |
    //  |   1  |   20 12  |    FIM P0, 0x12         |
    //  |   3  |    ...   |           ...           |
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  | fff  |    ...   |           ...           |
    //  =============================================
    //
    // So the address 2 won't be in table, cause it is already in the second row
    unsigned addrInTable = 0;

    // For the address number 1 and 2 there will be selected the same row
    // So we need to translate between addresses and row
    unsigned addrRow = 0;

    for (unsigned row = 0; row < code.size(); row++)
    {
        unsigned byte = code[row];
        unsigned command = byte;
        bool longCommand = Debugger::hasNextByte(byte);
        addrToRow.insert(std::pair<unsigned, unsigned>(row, addrRow));

        if (longCommand)
        {
            int low = code[++row];  // read the next byte
            command = (byte << 8) | low;   // combine code to 2 byte
            addrToRow.insert(std::pair<unsigned, unsigned>(row, addrRow));
        }
        addrRow++;

        this->insertRow(rows++);

        QTableWidgetItem* brkptItem = new QTableWidgetItem("", QTableWidgetItem::UserType);
        brkptItem->setTextAlignment(Qt::AlignCenter);
        brkptItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(rows-1, 0, brkptItem);
        items.push_back(brkptItem);

        QTableWidgetItem* addrItem = new QTableWidgetItem(Debugger::addressToString(addrInTable), QTableWidgetItem::UserType);
        addrItem->setTextAlignment(Qt::AlignCenter);
        addrItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(rows-1, 1, addrItem);
        items.push_back(addrItem);

        QTableWidgetItem* codeItem = new QTableWidgetItem(Debugger::commandToString(command), QTableWidgetItem::UserType);
        codeItem->setTextAlignment(Qt::AlignCenter);
        codeItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(rows-1, 2, codeItem);
        items.push_back(codeItem);

        QTableWidgetItem* commandItem = new QTableWidgetItem(Debugger::codeToInstruction(command), QTableWidgetItem::UserType);
        commandItem->setTextAlignment(Qt::AlignCenter);
        commandItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        this->setItem(rows-1, 3, commandItem);
        items.push_back(commandItem);

        if (longCommand)
        {
            addrInTable += 2;
        }
        else
        {
            addrInTable += 1;
        }
    }

    this->viewport()->update();
}

void DebuggerList::init()
{
    std::vector<unsigned> code(rowMaxNumbers); /// TODO check on all OS, if it fills the free space with zeroes
    this->setCode(code);
    this->selectAddress(0);
}

