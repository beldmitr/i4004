#ifndef CHOOSEIOWIDGET_H
#define CHOOSEIOWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>

#include <memory>
#include <iostream>

class ChooseIOWidget : public QWidget
{
    Q_OBJECT
private:
    std::shared_ptr<QVBoxLayout> layout;
    std::shared_ptr<QPushButton> button;
    std::shared_ptr<QMenu> menuButton;

    bool isDRAM = true;

public:
    explicit ChooseIOWidget(bool isDRAM, QWidget *parent = 0);
    virtual ~ChooseIOWidget();

    enum class IOType
    {
        NONE,
        ROM_IO,
        DRAM_IO
    };

signals:
    void onROMConnected(unsigned page, unsigned bit);
    void onDRAMConnected(unsigned bank, unsigned chip, unsigned bit); // Data RAM connection

    void onDisconnected();


public slots:
};

#endif // CHOOSEIOWIDGET_H
