#ifndef PROGRAMRAMWIDGET_H
#define PROGRAMRAMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollBar>
#include <QComboBox>
#include <QGridLayout>

#include <memory>

#include "Simulator/simulator.h"
#include "memorytable.h"

class ProgramRamWidget : public QWidget
{
    Q_OBJECT
private:
    Simulator* simulator;

    std::shared_ptr<QVBoxLayout> layout;
    std::shared_ptr<QGridLayout> titleLayout;
    std::shared_ptr<QComboBox> comboTitle;
    std::shared_ptr<QHBoxLayout> mainLayout;
    std::shared_ptr<QScrollBar> scroll;
    std::shared_ptr<QGroupBox> memoryGB;
    std::shared_ptr<QHBoxLayout> memLayout;
    std::shared_ptr<MemoryTable> memory;

    void setMemoryTitle(int value);

    const unsigned pagesNumber = 16; /// TODO this
    const unsigned bytesPerPage = 256; /// TODO this

public:
    explicit ProgramRamWidget(Simulator *simulator, QWidget *parent = 0);
    virtual ~ProgramRamWidget();

signals:

private slots:
    void handlePramCleared();
    void handlePramChanged(unsigned addr, unsigned value);
};

#endif // PROGRAMRAMWIDGET_H
