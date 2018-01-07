#ifndef LEDSUBWINDOW_H
#define LEDSUBWINDOW_H

#include <QObject>
#include <QWidget>
#include <QIcon>

#include <memory>
#include <vector>

#include <QGridLayout>

#include "Simulator/simulator.h"
#include "subwindow.h"
#include "led.h"


class LEDSubWindow : public SubWindow
{
    Q_OBJECT
public:
    explicit LEDSubWindow(Simulator* simulator);
    virtual ~LEDSubWindow();

private:
    Simulator* simulator;

    std::shared_ptr<QWidget> centralWidget;
    std::shared_ptr<QGridLayout> layout;
    std::vector<Led*> leds;

    const unsigned ledNumber = 16;
    const unsigned ledColumns = 4;

    // QWidget interface
protected:
    void changeEvent(QEvent *event);
};

#endif // LEDSUBWINDOW_H
