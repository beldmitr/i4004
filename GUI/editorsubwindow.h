#ifndef EDITORSUBWINDOW_H
#define EDITORSUBWINDOW_H

#include <QMessageBox>
#include <QFileDialog>
#include <QObject>
#include <QIcon>
#include <QTextEdit>

#include <memory>
#include <fstream>

#include "subwindow.h"
#include "editor.h"


class EditorSubWindow : public SubWindow
{
    Q_OBJECT
public:
    explicit EditorSubWindow(QWidget *parent = 0);
    virtual ~EditorSubWindow();

    void readFile();
    void writeFile();

    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void undoEdit();
    void redoEdit();
    void cutEdit();
    void copyEdit();
    void pasteEdit();
    void deleteEdit();
    void selectAllEdit();

    QString getFilename() const;

private:
    std::shared_ptr<Editor> editor;

    QString filename;

signals:
    void onTextChanged();
    void onCursorPosChanged(unsigned);

private slots:
    void handleCursorPosChanged();
};

#endif // EDITORSUBWINDOW_H
