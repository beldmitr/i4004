#ifndef SEVENSEGMENTSUBWINDOW_H
#define SEVENSEGMENTSUBWINDOW_H

#include <QObject>

#include <memory>

#include "subwindow.h"

class SevenSegmentSubWindow : public SubWindow
{
    Q_OBJECT
public:
    explicit SevenSegmentSubWindow();
    virtual ~SevenSegmentSubWindow();
};

#endif // SEVENSEGMENTSUBWINDOW_H
