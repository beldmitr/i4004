#ifndef LEDPANEL_H
#define LEDPANEL_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>

#include <memory>
#include <vector>

#include "led.h"
#include "coloredcombobox.h"
#include "chooseiowidget.h"

class LEDPanel : public QWidget
{
    Q_OBJECT
public:
    explicit LEDPanel();
    virtual ~LEDPanel();

private:
    std::shared_ptr<QGridLayout> layout;

    std::vector<ColoredComboBox*> comboBoxes;
    std::vector<LED*> leds;
    std::vector<ChooseIOWidget*> chooseIOs;

private slots:
    void update();
    void changeLedColor(QString color);

};

#endif // LEDPANEL_H
