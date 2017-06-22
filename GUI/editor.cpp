#include "editor.h"

Editor::Editor(QWidget *parent) : QWidget(parent)
{
    layout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(this));
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    panel = std::shared_ptr<QFrame>(new QFrame);
    text = std::shared_ptr<QTextEdit>(new QTextEdit);

    highliter = std::shared_ptr<Highlighter>(new Highlighter(text->document()));

    // Making minimal size according to screen resolution
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(desktop.primaryScreen());
    text->setMinimumSize(rect.size() / 4);

    panel->setMinimumWidth(100);
    panel->setCursor(Qt::PointingHandCursor);

    layout->addWidget(panel.get());
    layout->addWidget(text.get());

    connect(text.get(), &QTextEdit::textChanged, [=](){
        emit onTextChanged();
    });

    connect(text.get(), &QTextEdit::cursorPositionChanged, [=](){
        emit onCursorPositionChanged();
    });
}

Editor::~Editor()
{
    // delete here something or finalize
}

std::shared_ptr<QTextEdit> Editor::getText() const
{
    return text;
}

void Editor::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    // TODO implement here calculating and drawing line numbers
}
