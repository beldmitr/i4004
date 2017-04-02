#ifndef SEVENSEGMENTSUBWINDOW_H
#define SEVENSEGMENTSUBWINDOW_H

#include <QObject>
#include <QIcon>

#include <memory>

#include "subwindow.h"
#include "sevensegmentpanel.h"

class SevenSegmentSubWindow : public SubWindow
{
    Q_OBJECT
public:
    explicit SevenSegmentSubWindow();
    virtual ~SevenSegmentSubWindow();

private:
    std::shared_ptr<SevenSegmentPanel> sevenSegmentPanel;
};

#endif // SEVENSEGMENTSUBWINDOW_H
