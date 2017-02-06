#ifndef IOWIDGETN_H
#define IOWIDGETN_H

#include <QWidget>
#include <QGridLayout>

#include <memory>

#include "button.h"
#include "led.h"

class IOWidgetN : public QWidget
{
public:
    explicit IOWidgetN();
    virtual ~IOWidgetN();

private:
    std::shared_ptr<QGridLayout> layout;

};

#endif // IOWIDGETN_H
