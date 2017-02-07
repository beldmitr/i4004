#ifndef IOWIDGETN_H
#define IOWIDGETN_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>

#include <memory>

#include "button.h"
#include "led.h"
#include "coloredcombobox.h"

class IOWidgetN : public QWidget
{
    Q_OBJECT
public:
    explicit IOWidgetN();
    virtual ~IOWidgetN();

private:
    std::shared_ptr<QGridLayout> layout;

    std::shared_ptr<LED> led0;

    std::shared_ptr<ColoredComboBox> cbColored;

private slots:
    void update();
    void changeLedColor(QString color);

};

#endif // IOWIDGETN_H
