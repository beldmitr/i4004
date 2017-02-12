#ifndef LED_H
#define LED_H

#include <QObject>
#include <QImage>
#include <QLabel>

#include <memory>

class LED : public QLabel
{
    Q_OBJECT
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
    void setScale(double scale = 1);

    Color getColor() const;
    bool getIsOn() const;

    void setColor(LED::Color color);
    void setColor(QString color);

    void update();

private:
    QImage image;

    QString filenameOn;
    QString filenameOff;

    Color color;
    bool isOn;
    double scale;

signals:
    void changed();

public slots:
};

#endif // LED_H
