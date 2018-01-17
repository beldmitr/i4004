#include "editorsubwindow.h"

EditorSubWindow::EditorSubWindow(QWidget *parent) : SubWindow(parent)
{
    editor = std::shared_ptr<Editor>(new Editor(parent));

    this->setWidget(editor.get());
    this->setWindowTitle("Editor");
    this->setWindowIcon(QIcon(":/Resources/icons/editor.png"));

    this->move(5, 5);

    QRect desktop = QApplication::desktop()->screenGeometry();

    QRect r = this->geometry();
    r.setHeight((desktop.height() / 2) - 100);
    r.setWidth((desktop.width() / 2) - 100);
    this->setGeometry(r);

    connect(editor.get(), SIGNAL(cursorPositionChanged()), this, SLOT(handleCursorPosChanged()));
}

EditorSubWindow::~EditorSubWindow()
{
    // Delete here something or finalize
}

void EditorSubWindow::readFile()
{
    std::fstream file(filename.toStdString(), ios::in);

    if(file.is_open())
    {
        string line;
        QString doc;

        bool firstLine = true;

        while(getline(file, line))
        {
            if(firstLine)
            {
                firstLine = false;
            }
            else
            {
                doc.append("\n");
            }
            doc.append(line.c_str());
        }

        file.close();
        editor->setPlainText(doc);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Can't open file ").append(filename));
    }
}

void EditorSubWindow::writeFile()
{
    std::fstream file(filename.toStdString(), ios::out | ios::trunc);

    if (file.is_open())
    {
        QStringList lines = editor->toPlainText().split("\n");

        for (QString l : lines)
        {
            file << l.toStdString() << "\n";
        }

        file.close();
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Can't save to file ").append(filename));
    }
}

void EditorSubWindow::newFile()
{
    QString msg = tr("Please, don't forget to save your changes.\n\nDo you want to start a new file?");
    QMessageBox::StandardButton btn = QMessageBox::question(this, tr("New file"), msg);
    if (btn == QMessageBox::Yes)
    {
        editor->clear();
        editor->document()->setModified(false);

        this->filename.clear();
    }
}

void EditorSubWindow::openFile()
{
    QFileDialog openDlg;
    openDlg.setAcceptMode(QFileDialog::AcceptOpen);

    filename = openDlg.getOpenFileName(this, tr("Open File"), "", "Intel4004 assembler (*.asm);;All files (*.*)");
    if (!filename.isEmpty())
    {
        this->filename = filename;
        readFile();
    }
}

void EditorSubWindow::saveFile()
{
    if (filename.isEmpty())
    {
        saveAsFile();
    }
    else
    {
        writeFile();
    }
}

void EditorSubWindow::saveAsFile()
{
    QFileDialog saveAsDlg;
    saveAsDlg.setAcceptMode(QFileDialog::AcceptSave);

    QString filename = saveAsDlg.getSaveFileName(this, tr("Save File As"), "", "Intel4004 assembler (*.asm);;All files (*.*)");
    if (!filename.isEmpty())
    {
        this->filename = filename;
        writeFile();
    }
}

void EditorSubWindow::undoEdit()
{
    editor->undo();
}

void EditorSubWindow::redoEdit()
{
    editor->redo();
}

void EditorSubWindow::cutEdit()
{
    editor->cut();
}

void EditorSubWindow::copyEdit()
{
    editor->copy();
}

void EditorSubWindow::pasteEdit()
{
    editor->paste();
    editor->rehighlight();
}

void EditorSubWindow::deleteEdit()
{
    editor->textCursor().removeSelectedText();
}

void EditorSubWindow::selectAllEdit()
{
    editor->selectAll();
}

QString EditorSubWindow::getFilename() const
{
    return filename;
}

void EditorSubWindow::handleCursorPosChanged()
{
    QTextCursor tc = editor->textCursor();
    unsigned lineNumber = tc.block().blockNumber() + 1;

    emit onCursorPosChanged(lineNumber);
}
