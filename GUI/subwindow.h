#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QCloseEvent>
#include <QEvent>
#include <QWindowStateChangeEvent>

#include <iostream>

using namespace std;

class SubWindow : public QMdiSubWindow
{
    Q_OBJECT
private:


public:
    explicit SubWindow(QWidget *parent = 0);
    virtual ~SubWindow();

signals:

public slots:

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *);

};

#endif // SUBWINDOW_H
