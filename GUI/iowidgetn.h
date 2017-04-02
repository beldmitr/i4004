#ifndef IOWIDGETN_H
#define IOWIDGETN_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>

#include <memory>
#include <vector>

#include "button.h"
#include "led.h"
#include "coloredcombobox.h"
#include "chooseiowidget.h"

class IOWidgetN : public QWidget
{
    Q_OBJECT
public:
    explicit IOWidgetN();
    virtual ~IOWidgetN();

private:
    std::shared_ptr<QGridLayout> layout;

    std::vector<ColoredComboBox*> comboBoxes;
    std::vector<LED*> leds;
    std::vector<ChooseIOWidget*> chooseIOs;

private slots:  /// TODO reduce it to "slots:" only, because "slots" means "private slots". Check this and reduce
    void update();
    void changeLedColor(QString color);

};

#endif // IOWIDGETN_H
