#ifndef COLOREDCOMBOBOX_H
#define COLOREDCOMBOBOX_H

#include <QComboBox>
#include <QObject>
#include <QStringList>

#include <memory>

#include "led.h"

class ColoredComboBox : public QComboBox
{
public:
    explicit ColoredComboBox(LED* led);
    virtual ~ColoredComboBox();

    LED* getLed() const;    /// TODO make it return smart ptr ??

private:
    // I didn't create this pointer with keyword new, so I don't have to delete it. I assign it only threw a parameter in a constructor
    LED* led; /// TODO maybe make it smart ??

};

#endif // COLOREDCOMBOBOX_H
