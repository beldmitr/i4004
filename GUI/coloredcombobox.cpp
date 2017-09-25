#include "coloredcombobox.h"

ColoredComboBox::ColoredComboBox()
{
    this->setMaximumWidth(125);

    QStringList itemList;
    itemList << tr("Red") << tr("Blue") << tr("Green") << tr("Orange") << tr("Pink") << tr("Yellow");

    for (int i = 0; i < itemList.size(); i++)
    {
        QColor color(itemList[i]);

        this->insertItem(i, itemList[i]);
        this->setItemData(i, color, Qt::DecorationRole);
    }
}

ColoredComboBox::~ColoredComboBox()
{

}

