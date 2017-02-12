#include "coloredcombobox.h"

// TODO Change pink color to magenta or darkMagenta
ColoredComboBox::ColoredComboBox(LED* led) : QComboBox()
{
    this->led = led;

    QStringList itemList;
    itemList << tr("Blue") << tr("Green") << tr("Orange") << tr("Pink") << tr("Red") << tr("Yellow");

    for (int i = 0; i < itemList.size(); i++)
    {
        QColor color(itemList[i]);

        this->insertItem(i, itemList[i]);
        this->setItemData(i, color, Qt::DecorationRole);
    }
}

ColoredComboBox::~ColoredComboBox()
{
    // delete here something
    led = nullptr;
}

LED* ColoredComboBox::getLed() const
{
    return led;
}
