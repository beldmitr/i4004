#include "coloredcombobox.h"

ColoredComboBox::ColoredComboBox() : QComboBox()
{
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
}
