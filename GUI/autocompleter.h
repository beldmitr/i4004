#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <QCompleter>

class AutoCompleter : public QCompleter
{
    Q_OBJECT
public:
    AutoCompleter(QObject *parent);

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // AUTOCOMPLETER_H
