#ifndef EDITORSUBWINDOW_H
#define EDITORSUBWINDOW_H

#include <QObject>
#include <QIcon>
#include <QTextEdit>

#include <memory>

#include "subwindow.h"
#include "editor.h"

class EditorSubWindow : public SubWindow
{
    Q_OBJECT
public:
    explicit EditorSubWindow();
    virtual ~EditorSubWindow();

    QTextEdit* getTextEditor();

private:
    std::shared_ptr<Editor> editor;
};

#endif // EDITORSUBWINDOW_H
