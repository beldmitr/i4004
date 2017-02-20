#ifndef BUTTONPANEL_H
#define BUTTONPANEL_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include <memory>

#include "button.h"
#include "chooseiowidget.h"

class ButtonPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonPanel(QWidget *parent = 0);
    virtual ~ButtonPanel();

private:
    std::shared_ptr<QGridLayout> layout;

signals:

public slots:
};

#endif // BUTTONPANEL_H
