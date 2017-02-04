#ifndef LED_H
#define LED_H

#include <QImage>

class LED : public QImage
{
public:
    enum class Color
    {
        NONE,
        RED,
        ORANGE,
        YELLOW,
        GREEN,
        BLUE,
        PINK
    };

    explicit LED(LED::Color color);
    virtual ~LED();

    void on();
    void off();

    Color getColor() const;
    bool getIsOn() const;

private:
    QString filenameOn;
    QString filenameOff;

    Color color;
    bool isOn;

signals:

public slots:
};

#endif // LED_H
