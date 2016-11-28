#ifndef IOWIDGET_H
#define IOWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QListWidget>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QPainter>

#include <iostream>

class QDragEnterEvent;

class ioWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit ioWidget(QWidget *parent = 0);

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // IOWIDGET_H
