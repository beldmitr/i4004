#include "autocompleter.h"

AutoCompleter::AutoCompleter(QObject* parent) : QCompleter(parent)
{
    // TODO implement this completer
}

bool AutoCompleter::eventFilter(QObject *watched, QEvent *event)
{
    return QCompleter::eventFilter(watched, event);
}
