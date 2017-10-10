#ifndef DEBUGGERLIST_H
#define DEBUGGERLIST_H

#include <QWidget>
#include <QTableWidget>

class DebuggerList : public QTableWidget
{
    Q_OBJECT
public:
    explicit DebuggerList(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // DEBUGGERLIST_H
