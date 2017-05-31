#include "editorsubwindow.h"

EditorSubWindow::EditorSubWindow() : SubWindow()
{
    editor = std::shared_ptr<Editor>(new Editor);

    this->setWidget(editor.get());
    this->setWindowTitle("Editor");
    this->setWindowIcon(QIcon(":/Resources/icons/editor.png"));

    connect(editor.get(), &Editor::onTextChanged,
            [=](){
                emit onTextChanged();
            });

    connect(editor.get(), &Editor::onCursorPositionChanged,
            [=](){
                emit onCursorPositionChanged();
            });
}

EditorSubWindow::~EditorSubWindow()
{
    // Delete here something or finalize
}

void EditorSubWindow::clearEditor()
{
    this->editor->clear();
}
