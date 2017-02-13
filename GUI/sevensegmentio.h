#ifndef SEVENSEGMENTIO_H
#define SEVENSEGMENTIO_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

#include <map>

class SevenSegmentIO : public QLabel
{
    Q_OBJECT
public:
    enum class Pins
    {
        A, B, C, D, E, F, G, DP
    };
    explicit SevenSegmentIO(QWidget *parent = 0);
    virtual ~SevenSegmentIO();

    void setPin(SevenSegmentIO::Pins pin, bool isTurnOn);

private:

    void init();

    enum class PinType
    {
        Vertical,
        Horizontal,
        Point
    };

    struct Picture
    {
        QPoint position;
        QImage imageOn;
        QImage imageOff;
    };

    std::map<SevenSegmentIO::Pins, Picture> mapPins;

    QImage image;

    QImage imagePinVerticalOn;
    QImage imagePinVerticalOff;

    QImage imagePinHorizontalOn;
    QImage imagePinHorizontalOff;

    QImage imagePinPointOn;
    QImage imagePinPointOff;

    double scaled;

signals:
    void clicked(QMouseEvent* event);

public slots:

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // SEVENSEGMENTIO_H
