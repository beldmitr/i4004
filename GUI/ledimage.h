#ifndef LEDIMAGE_H
#define LEDIMAGE_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QLabel>

#include <map>
#include <memory>

class LedImage : public QLabel
{
    Q_OBJECT
public:
    explicit LedImage(QWidget *parent = 0);
    virtual ~LedImage();
    void light(bool isLight);
    void setColor(QString color);

private:
    void paint();

    bool isLight;
    std::map<QString, QImage> pics;

    // I delete image_on and image_off pointersr from the map
    QImage image_on;
    QImage image_off;

signals:
    void onLightChanged();
    void onColorChanged();

public slots:

};

#endif // LEDIMAGE_H
