#ifndef IOWIDGETN_H
#define IOWIDGETN_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>

#include <memory>

#include "button.h"
#include "led.h"

class IOWidgetN : public QWidget
{
    Q_OBJECT
public:
    explicit IOWidgetN();
    virtual ~IOWidgetN();

private:
    std::shared_ptr<QGridLayout> layout;



    std::shared_ptr<LED> led0;

private slots:
    void update();

};

#endif // IOWIDGETN_H
