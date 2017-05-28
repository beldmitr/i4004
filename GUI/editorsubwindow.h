#ifndef EDITORSUBWINDOW_H
#define EDITORSUBWINDOW_H

#include <QObject>
#include <QIcon>
#include <QTextEdit>

#include <memory>

#include "subwindow.h"
#include "editor.h"
#include "highlighter.h"

class EditorSubWindow : public SubWindow
{
    Q_OBJECT
public:
    explicit EditorSubWindow();
    virtual ~EditorSubWindow();

    QTextEdit* getTextEditor();

private:
    std::shared_ptr<Editor> editor;
    std::shared_ptr<Highlighter> highliter;
};

#endif // EDITORSUBWINDOW_H
