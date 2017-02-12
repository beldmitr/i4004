#ifndef CHOOSEIOWIDGET_H
#define CHOOSEIOWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>

#include <memory>

class ChooseIOWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseIOWidget(QWidget *parent = 0);
    virtual ~ChooseIOWidget();

private:
    std::shared_ptr<QVBoxLayout> layout;
    std::shared_ptr<QPushButton> button;
    std::shared_ptr<QMenu> menuButton;


signals:

public slots:
};

#endif // CHOOSEIOWIDGET_H
