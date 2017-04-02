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

private:
    QGridLayout* layout;    /// TODO smart ptr

    QComboBox* countBox;    /// TODO smart ptr

    std::vector<SevenSegmentIO*> vectSevenSegment;  /// TODO smart ptr
    std::vector<ChooseIOWidget*> vectChooser;   /// TODO smart ptr

    void init(unsigned int countSegments);

public:
    explicit SevenSegmentPanel(QWidget *parent = 0);
    virtual ~SevenSegmentPanel();

signals:
    void changedSegmentCount();

public slots:
    void spinnerChanged(QString value);

};

#endif // SEVENSEGMENTPANEL_H
