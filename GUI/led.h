#ifndef LED_H
#define LED_H

#include <QImage>

class LED : public QImage
{
    Q_OBJECT
public:
    explicit LED(QWidget *parent = 0);
    virtual ~LED();

signals:

public slots:
};

#endif // LED_H
