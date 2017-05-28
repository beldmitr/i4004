#include "editor.h"

Editor::Editor(QWidget *parent) : QWidget(parent)
{
    layout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(this));
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    panel = std::shared_ptr<QFrame>(new QFrame);
    edit = std::shared_ptr<QTextEdit>(new QTextEdit);

    // Making minimal size according to screen resolution
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(desktop.primaryScreen());
    edit->setMinimumSize(rect.size() / 4);

    panel->setMinimumWidth(100);
    panel->setCursor(Qt::PointingHandCursor);

    layout->addWidget(panel.get());
    layout->addWidget(edit.get());
}

Editor::~Editor()
{
    // delete here something or finalize
}

QTextEdit* Editor::getTextEditor()
{
    return edit.get();
}


void Editor::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    // TODO implement here calculating and drawing line numbers
}
