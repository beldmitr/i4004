#include "editorsubwindow.h"

EditorSubWindow::EditorSubWindow() : SubWindow()
{
    editor = std::shared_ptr<Editor>(new Editor);
    highliter = std::shared_ptr<Highlighter>(new Highlighter(editor->getTextEditor()->document()));

    this->setWidget(editor.get());
    this->setWindowTitle("Editor");
    this->setWindowIcon(QIcon(":/Resources/icons/editor.png"));
}

EditorSubWindow::~EditorSubWindow()
{

}

QTextEdit*EditorSubWindow::getTextEditor()
{
    return editor->getTextEditor();
}
