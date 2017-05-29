#include "autocompleter.h"

AutoCompleter::AutoCompleter(QObject* parent) : QCompleter(parent)
{

}

bool AutoCompleter::eventFilter(QObject *watched, QEvent *event)
{
    return QCompleter::eventFilter(watched, event);
}
