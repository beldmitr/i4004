#ifndef BUTTONSUBWINDOW_H
#define BUTTONSUBWINDOW_H

#include <QObject>
#include <QIcon>

#include <memory>

#include "subwindow.h"
#include "buttonpanel.h"

class ButtonSubWindow : public SubWindow
{
    Q_OBJECT
public:
    ButtonSubWindow();
    virtual ~ButtonSubWindow();

private:
    std::shared_ptr<ButtonPanel> buttonPanel;
};

#endif // BUTTONSUBWINDOW_H
