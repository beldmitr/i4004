#ifndef STACKWIDGET_H
#define STACKWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTextEdit>

class StackWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit StackWidget(QWidget *parent = 0);
    virtual ~StackWidget();

private:
    QGridLayout* layout;

    QLabel* lblPC;
    QLabel* lblLevel1;
    QLabel* lblLevel2;
    QLabel* lblLevel3;

    QTextEdit* edtPC;
    QTextEdit* edtLevel1;
    QTextEdit* edtLevel2;
    QTextEdit* edtLevel3;

signals:

public slots:
};

#endif // STACKWIDGET_H
