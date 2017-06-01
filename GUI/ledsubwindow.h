#ifndef LEDSUBWINDOW_H
#define LEDSUBWINDOW_H

#include <QObject>
#include <QWidget>
#include <QIcon>

#include <memory>
#include <vector>

#include <QHBoxLayout>

#include "subwindow.h"
#include "led.h"


class LEDSubWindow : public SubWindow
{
    Q_OBJECT
public:
    explicit LEDSubWindow();
    virtual ~LEDSubWindow();

private:
    std::shared_ptr<QWidget> centralWidget;
    std::shared_ptr<QHBoxLayout> layout;
    std::vector<Led*> leds;
};

#endif // LEDSUBWINDOW_H
