#ifndef IOLISTCOMPONENTS_H
#define IOLISTCOMPONENTS_H

#include <QWidget>
#include <QListWidget>

class ioListComponents : public QListWidget
{
    Q_OBJECT
public:
    explicit ioListComponents(QWidget *parent = 0);

protected:
     void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // IOLISTCOMPONENTS_H
