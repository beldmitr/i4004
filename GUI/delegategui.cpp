#include "delegategui.h"

DelegateGUI::DelegateGUI(std::shared_ptr<RomWidget> romWidget,
                         std::shared_ptr<DataRamWidgetN> dramWidget,
                         std::shared_ptr<ProgramRamWidget> pramWidget,
                         std::shared_ptr<ProcessorWidget> cpuWidget)
{
    this->romWidget = romWidget;
    this->dramWidget = dramWidget;
    this->pramWidget = pramWidget;
    this->cpuWidget = cpuWidget;
}

void DelegateGUI::setCpu(std::shared_ptr<CPU> cpu)
{
    this->cpu = cpu;
}

void DelegateGUI::setRom(std::shared_ptr<ROM> rom)
{
    this->rom = rom;
}

void DelegateGUI::setPram(std::shared_ptr<PRAM> pram)
{
    this->pram = pram;
}

void DelegateGUI::setDram(std::shared_ptr<DRAM> dram)
{
    this->dram = dram;
}

void DelegateGUI::updateRomGui()
{


    romWidget->update();
}

void DelegateGUI::updateDramGui()
{

    dramWidget->update();
}

void DelegateGUI::updatePramGui()
{
    pramWidget->update();
}

void DelegateGUI::updateCpuGui()
{
//    item->setText(0,"wert");

//    QTreeWidgetItem* accumItem = new QTreeWidgetItem();
//    accumItem->setText(0, "Accumulator");
//    QLabel* accumLabel = new QLabel("0x12");
//    delete cpuWidget->itemAt(0, 0);
//    cpuWidget->setItemWidget(accumItem, 1, accumLabel);
}

void DelegateGUI::updateAllGui()
{
    updateRomGui();
    updateDramGui();
    updatePramGui();
    updateCpuGui();
}

