#ifndef SEVENSEGMENTPANEL_H
#define SEVENSEGMENTPANEL_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QMenu>
#include <QWidgetAction>
#include <QStringList>
#include <QComboBox>

#include <vector>
#include <memory>

#include "sevensegmentio.h"
#include "chooseiowidget.h"

class SevenSegmentPanel : public QWidget
{
    Q_OBJECT
public:
    explicit SevenSegmentPanel(QWidget *parent = 0);
    virtual ~SevenSegmentPanel();

private:
    QGridLayout* layout;

    QComboBox* countBox;

    std::vector<SevenSegmentIO*> vectSevenSegment;
    std::vector<ChooseIOWidget*> vectChooser;

    void init(unsigned int countSegments);

signals:
    void changedSegmentCount();

public slots:
    void spinnerChanged(QString value);

};

#endif // SEVENSEGMENTPANEL_H
