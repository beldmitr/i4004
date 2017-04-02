#include "editorsubwindow.h"

EditorSubWindow::EditorSubWindow() : SubWindow()
{
    editor = std::shared_ptr<Editor>(new Editor);

    this->setWidget(editor.get());
    this->setWindowTitle("Editor");
    this->setWindowIcon(QIcon(":/Resources/icons/editor.png"));
}

EditorSubWindow::~EditorSubWindow()
{

}
