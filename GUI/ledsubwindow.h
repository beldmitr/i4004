#ifndef LEDSUBWINDOW_H
#define LEDSUBWINDOW_H

#include <QObject>

#include <memory>

#include "subwindow.h"
#include "ledpanel.h"

class LEDSubWindow : public SubWindow
{
    Q_OBJECT
public:
    explicit LEDSubWindow();
    virtual ~LEDSubWindow();

private:
    std::shared_ptr<LEDPanel> ledPanel;
};

#endif // LEDSUBWINDOW_H
