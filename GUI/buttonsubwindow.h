#ifndef BUTTONSUBWINDOW_H
#define BUTTONSUBWINDOW_H

#include <QObject>
#include <QIcon>
#include <QGridLayout>

#include <memory>
#include <vector>

#include "Simulator/simulator.h"
#include "subwindow.h"
#include "button.h"
#include "chooseiowidget.h"



class ButtonSubWindow : public SubWindow
{
    Q_OBJECT
public:
    explicit ButtonSubWindow(Simulator* simulator);
    virtual ~ButtonSubWindow();

private:
    Simulator* simulator;
    std::shared_ptr<QWidget> centralWidget;
    std::shared_ptr<QGridLayout> layout;

    std::vector<Button*> buttons;
    std::vector<ChooseIOWidget*> connectors;

    const unsigned buttonNumber = 15;
    const unsigned buttonColumns = 3;


    // QWidget interface
protected:
    void changeEvent(QEvent *event);
};

#endif // BUTTONSUBWINDOW_H
