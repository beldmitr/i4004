#ifndef DELEGATEGUI_H
#define DELEGATEGUI_H

#include <memory>

#include <QTreeWidgetItem>
#include <QAbstractItemDelegate>

#include "rom.h"
#include "pram.h"
#include "dram.h"
#include "cpu.h"

#include "GUI/dataramwidgetn.h"
#include "GUI/programramwidget.h"
#include "GUI/romwidget.h"
#include "GUI/processorwidget.h"


class DelegateGUI
{
private:
    std::shared_ptr<CPU> cpu;
    std::shared_ptr<ROM> rom;
    std::shared_ptr<PRAM> pram;
    std::shared_ptr<DRAM> dram;

    std::shared_ptr<DataRamWidgetN> dramWidget;
    std::shared_ptr<RomWidget> romWidget;
    std::shared_ptr<ProgramRamWidget> pramWidget;
    std::shared_ptr<ProcessorWidget> cpuWidget;

public:
    DelegateGUI(std::shared_ptr<RomWidget> romWidget,
                std::shared_ptr<DataRamWidgetN> dramWidget,
                std::shared_ptr<ProgramRamWidget> pramWidget,
                std::shared_ptr<ProcessorWidget> cpuWidget);

    void setCpu(std::shared_ptr<CPU> cpu);
    void setRom(std::shared_ptr<ROM> rom);
    void setPram(std::shared_ptr<PRAM> pram);
    void setDram(std::shared_ptr<DRAM> dram);

    void updateRomGui();
    void updateDramGui();
    void updatePramGui();
    void updateCpuGui();

    void updateAllGui();
};

#endif // DELEGATEGUI_H
