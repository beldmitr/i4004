#ifndef LED_H
#define LED_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include <memory>
#include <iostream>

#include "ledimage.h"
#include "coloredcombobox.h"
#include "chooseiowidget.h"

class Led : public QWidget
{
    Q_OBJECT
public:
    explicit Led(QWidget *parent = 0);

private:
    std::shared_ptr<LedImage> ledImage;
    std::shared_ptr<ColoredComboBox> coloredComboBox;
    std::shared_ptr<ChooseIOWidget> connector;

    std::shared_ptr<QGridLayout> layout;


signals:

private slots:
    void coloredComboboxChanged(QString color);

public slots:
};

#endif // LED_H
