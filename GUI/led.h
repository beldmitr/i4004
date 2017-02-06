#ifndef LED_H
#define LED_H

#include <QImage>
#include <QLabel>

class LED : public QLabel
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

    void setTurnOn(bool light = true);
    void scaled(double scale = 1);

    Color getColor() const;
    bool getIsOn() const;

    void setColor(LED::Color color);

    void update();

private:
    QImage image;

    QString filenameOn;
    QString filenameOff;

    Color color;
    bool isOn;
    double scale;

signals:

public slots:
};

#endif // LED_H
