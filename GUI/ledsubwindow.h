#ifndef LEDSUBWINDOW_H
#define LEDSUBWINDOW_H

#include <QObject>
#include <QWidget>
#include <QIcon>

#include <memory>
#include <vector>

#include <QHBoxLayout>

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
    std::shared_ptr<QHBoxLayout> layout;
    std::vector<Led*> leds;

    // QWidget interface
protected:
    void changeEvent(QEvent *event);
};

#endif // LEDSUBWINDOW_H
