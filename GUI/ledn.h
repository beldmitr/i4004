#ifndef LEDN_H
#define LEDN_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include <memory>
#include <iostream>

#include "ledimage.h"
#include "coloredcombobox.h"
#include "chooseiowidget.h"

class LedN : public QWidget
{
    Q_OBJECT
public:
    explicit LedN(QWidget *parent = 0);

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

#endif // LEDN_H
