#ifndef PROGRAMRAMWIDGET_H
#define PROGRAMRAMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollBar>
#include <QComboBox>

#include <memory>

#include "memorytable.h"

class ProgramRamWidget : public QWidget
{
    Q_OBJECT
private:
    std::shared_ptr<QVBoxLayout> layout;
    std::shared_ptr<QHBoxLayout> titleLayout;
    std::shared_ptr<QComboBox> comboTitle;
    std::shared_ptr<QHBoxLayout> mainLayout;
    std::shared_ptr<QScrollBar> scroll;
    std::shared_ptr<QGroupBox> memoryGB;
    std::shared_ptr<QHBoxLayout> memLayout;
    std::shared_ptr<MemoryTable> memory;

    void setMemoryTitle(int value);

public:
    explicit ProgramRamWidget(QWidget *parent = 0);
    virtual ~ProgramRamWidget();

signals:

public slots:
};

#endif // PROGRAMRAMWIDGET_H
