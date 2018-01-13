#include "editor.h"

Editor::Editor(QWidget *parent) : QTextEdit(parent)
{
    highliter = std::shared_ptr<Highlighter>(new Highlighter(this->document()));

    QStringList words = fileToList(":/Resources/completer.txt");
    completer = std::shared_ptr<QCompleter>(new QCompleter(words, this));
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    connect(completer.get(), SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));

//    this->setMinimumHeight(525);
//    this->setMinimumWidth(675);

    this->setMouseTracking(true);

    QFont font = this->font();
    QFontMetrics metrics(font);
    this->setTabStopWidth(tabStop * metrics.width(' '));
}

Editor::~Editor()
{
    // delete here something or finalize
}

void Editor::keyPressEvent(QKeyEvent *event)
{
    if (completer && completer->popup()->isVisible())
    {
        switch (event->key()) {
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
                event->ignore();
                return;
            default:
                break;
        }
    }

    bool isShortcut = ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_E); // CTRL+E
    if (!completer || !isShortcut) // do not process the shortcut when we have a completer
    {
        QTextEdit::keyPressEvent(event);
    }

    const bool ctrlOrShift = event->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!completer || (ctrlOrShift && event->text().isEmpty()))
    {
        return;
    }

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (event->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || event->text().isEmpty() || completionPrefix.length() < 1
                        || eow.contains(event->text().right(1)))) {
        completer->popup()->hide();
        return;
    }

    if (completionPrefix != completer->completionPrefix()) {
        completer->setCompletionPrefix(completionPrefix);
        completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
    }

    QRect cr = cursorRect();
    cr.setWidth(completer->popup()->sizeHintForColumn(0) + completer->popup()->verticalScrollBar()->sizeHint().width());
    completer->complete(cr);


}

void Editor::insertCompletion(const QString& completion)
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    tc.removeSelectedText();

    tc.insertText(completion + " ");

    setTextCursor(tc);
}

QString Editor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText().trimmed();
}

QStringList Editor::fileToList(const QString &filename) const
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly))
    {
        return QStringList();
    }

    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
    }
    return words;
}

void Editor::rehighlight()
{
    highliter->rehighlight();
}

void Editor::focusInEvent(QFocusEvent *event)
{
    if (completer)
    {
        completer->setWidget(this);
    }
    QTextEdit::focusInEvent(event);
}

