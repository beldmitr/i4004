#include "mainwindow.h"

void MainWindow::createActions()
{
    // Actions File
    actNew = new QAction(tr("&New"), this);
    actNew->setIcon(QIcon(":/Resources/icons/new.png"));
    actNew->setShortcut(QKeySequence::New);
    connect(actNew, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    actOpen = new QAction(tr("&Open"), this);
    actOpen->setIcon(QIcon(":/Resources/icons/open.png"));
    actOpen->setShortcut(QKeySequence::Open);
    connect(actOpen, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    actSave = new QAction(tr("&Save"), this);
    actSave->setIcon(QIcon(":/Resources/icons/save.png"));
    actSave->setShortcut(QKeySequence::Save);
    connect(actSave, SIGNAL(triggered(bool)), this, SLOT(saveFile()));

    actSaveAs = new QAction(tr("Save As..."), this);
    actSaveAs->setIcon(QIcon(":/Resources/icons/saveas.png"));
    actSaveAs->setShortcut(QKeySequence::SaveAs);
    connect(actSaveAs, SIGNAL(triggered(bool)), this, SLOT(saveAsFile()));

    actExit = new QAction(tr("E&xit"), this);
    actExit->setIcon(QIcon(":/Resources/icons/exit.png"));
    actExit->setShortcut(tr("Ctrl+Q"));
    connect(actExit, SIGNAL(triggered(bool)), this, SLOT(exitFile()));

    // Actions Edit
    actUndo = new QAction(tr("Undo"), this);
    actUndo->setIcon(QIcon(":/Resources/icons/undo.png"));
    actUndo->setShortcut(QKeySequence::Undo);
    connect(actUndo, SIGNAL(triggered(bool)), this, SLOT(undoEdit()));

    actRedo = new QAction(tr("Redo"), this);
    actRedo->setIcon(QIcon(":/Resources/icons/redo.png"));
    actRedo->setShortcut(QKeySequence::Redo);
    connect(actNew, SIGNAL(triggered(bool)), this, SLOT(redoEdit()));

    actCut = new QAction(tr("Cut"), this);
    actCut->setIcon(QIcon(":/Resources/icons/cut.png"));
    actCut->setShortcut(QKeySequence::Cut);
    connect(actCut, SIGNAL(triggered(bool)), this, SLOT(cutEdit()));

    actCopy = new QAction(tr("Copy"), this);
    actCopy->setIcon(QIcon(":/Resources/icons/copy.png"));
    actCopy->setShortcut(QKeySequence::Copy);
    connect(actCopy, SIGNAL(triggered(bool)), this, SLOT(copyEdit()));

    actPaste = new QAction(tr("Paste"), this);
    actPaste->setIcon(QIcon(":/Resources/icons/paste.png"));
    actPaste->setShortcut(QKeySequence::Paste);
    connect(actPaste, SIGNAL(triggered(bool)), this, SLOT(pasteEdit()));

    actDelete = new QAction(tr("Delete"), this);
    actDelete->setIcon(QIcon(":/Resources/icons/delete.png"));
    actDelete->setShortcut(QKeySequence::Delete);
    connect(actDelete, SIGNAL(triggered(bool)), this, SLOT(deleteEdit()));

    actSelectAll = new QAction(tr("Select All"), this);
    actSelectAll->setIcon(QIcon(":/Resources/icons/selectall.png"));
    actSelectAll->setShortcut(QKeySequence::SelectAll);
    connect(actSelectAll, SIGNAL(triggered(bool)), this, SLOT(selectAllEdit()));

    // Actions Build
    actCompile = new QAction(tr("Compile"), this);
    actCompile->setIcon(QIcon(":/Resources/icons/compile.png"));
    actCompile->setShortcut(tr("Ctrl+B"));
    actCompile->setDisabled(true);
    connect(actCompile, SIGNAL(triggered(bool)), this, SLOT(compileBuild()));

    actRun = new QAction(tr("Run"), this);
    actRun->setIcon(QIcon(":/Resources/icons/run.png"));
    actRun->setShortcut(tr("F5"));
    actRun->setDisabled(true);
    connect(actRun, SIGNAL(triggered(bool)), this, SLOT(runBuild()));

    actCompileRun = new QAction(tr("Compile and Run"), this);
    actCompileRun->setIcon(QIcon(":/Resources/icons/compile_run.png"));
    actCompileRun->setShortcut(tr("Ctrl+R"));
    actCompileRun->setDisabled(true);
    connect(actCompileRun, SIGNAL(triggered(bool)), this, SLOT(compileRunBuild()));

    actStep = new QAction(tr("Step"), this);
    //    actStep->setIcon(QIcon(":/Resources/icons/step.png")); // TODO icon
    //    actStep->setShortcut(tr("Ctrl+R"));   // TODO shortcut
    connect(actStep, SIGNAL(triggered(bool)), this, SLOT(step()));
}

void MainWindow::createMenu()
{
    mainMenu = std::shared_ptr<QMenuBar>(new QMenuBar);
    this->setMenuBar(mainMenu.get());

    QMenu *menuFile = mainMenu->addMenu("File");
    menuFile->addAction(actNew);
    menuFile->addAction(actOpen);
    menuFile->addSeparator();
    menuFile->addAction(actSave);
    menuFile->addAction(actSaveAs);
    menuFile->addSeparator();
    menuFile->addAction(actExit);

    QMenu *menuEdit = mainMenu->addMenu("Edit");
    menuEdit->addAction(actUndo);
    menuEdit->addAction(actRedo);
    menuEdit->addSeparator();
    menuEdit->addAction(actCut);
    menuEdit->addAction(actCopy);
    menuEdit->addAction(actPaste);
    menuEdit->addAction(actDelete);
    menuEdit->addSeparator();
    menuEdit->addAction(actSelectAll);

    QMenu *menuBuild = mainMenu->addMenu("Build");
    menuBuild->addAction(actCompile);
    menuBuild->addAction(actRun);
    menuBuild->addSeparator();
    menuBuild->addAction(actCompileRun);

    mainMenu->addMenu("Preferences");


    QMenu* menuWindows = mainMenu->addMenu("Windows");
    QAction* nextWindow = new QAction("Next window", this);
    connect(nextWindow, SIGNAL(triggered(bool)), mdi, SLOT(activateNextSubWindow()));
    menuWindows->addAction(nextWindow);

    QAction* prevWindow = new QAction("Previous window", this);
    connect(prevWindow, SIGNAL(triggered(bool)), mdi, SLOT(activatePreviousSubWindow()));
    menuWindows->addAction(prevWindow);

    menuWindows->addSeparator();

    for(QMdiSubWindow* w : mdi->subWindowList())
    {
        QAction* act = new QAction(w->windowTitle(), this);
        connect(act, SIGNAL(triggered(bool)), w, SLOT(show()));
        connect(act, SIGNAL(triggered(bool)), w, SLOT(setFocus()));
        menuWindows->addAction(act);
    }

    menuWindows->addSeparator();

    QAction* minimizeAll = new QAction("Minimize all", this);
    for(QMdiSubWindow* w : mdi->subWindowList())
    {
        connect(minimizeAll, SIGNAL(triggered(bool)), w, SLOT(showMinimized()));
    }
    menuWindows->addAction(minimizeAll);

    QAction* showWindows = new QAction("Show windows", this);
    for(QMdiSubWindow* w : mdi->subWindowList())
    {
        connect(showWindows, SIGNAL(triggered(bool)), w, SLOT(showNormal()));
    }
    connect(showWindows, SIGNAL(triggered(bool)), mdi, SLOT(tileSubWindows()));

    menuWindows->addAction(showWindows);

    mainMenu->addMenu("Help");
}

void MainWindow::createToolbars()
{
    toolBarMinimize = std::shared_ptr<QToolBar>(new QToolBar("Minimize"));
    for(QMdiSubWindow* w : mdi->subWindowList())
    {
        QIcon ico = w->windowIcon();
        QString title = w->windowTitle();

        QAction* act = new QAction(ico, title, this);
        act->setToolTip("Show " + title);

        connect(act, SIGNAL(triggered(bool)), w, SLOT(show()));
        connect(act, SIGNAL(triggered(bool)), w, SLOT(setFocus()));

        toolBarMinimize->addAction(act);
    }

    toolBarMinimize->setFloatable(false);
    toolBarMinimize->setMovable(false);

    toolBarFile = std::shared_ptr<QToolBar>(new QToolBar("File"));
    toolBarFile->addAction(actNew);
    toolBarFile->addAction(actOpen);
    toolBarFile->addAction(actSave);

    toolBarEdit = std::shared_ptr<QToolBar>(new QToolBar("Edit"));
    toolBarEdit->addAction(actUndo);
    toolBarEdit->addAction(actRedo);
    toolBarEdit->addSeparator();
    toolBarEdit->addAction(actCut);
    toolBarEdit->addAction(actCopy);
    toolBarEdit->addAction(actPaste);
    toolBarEdit->addAction(actDelete);
    toolBarEdit->addSeparator();
    toolBarEdit->addAction(actSelectAll);

    toolBarBuild = std::shared_ptr<QToolBar>(new QToolBar("Build"));
    toolBarBuild->addAction(actCompile);
    toolBarBuild->addAction(actRun);
    toolBarBuild->addAction(actCompileRun);

    toolBarDebug = std::shared_ptr<QToolBar>(new QToolBar("Debug"));
    toolBarDebug->addAction("Run");     // TODO action
    toolBarDebug->addAction("Stop");    // TODO action
    toolBarDebug->addAction(actStep);
    toolBarDebug->addAction("Reset");   // TODO action

    this->addToolBar(toolBarFile.get());
    this->addToolBar(toolBarEdit.get());
    this->addToolBar(toolBarBuild.get());
    this->addToolBar(toolBarDebug.get());
    this->addToolBar(Qt::LeftToolBarArea, toolBarMinimize.get());
}

void MainWindow::createSubWindows()
{

    SubWindow* editorWindow = new SubWindow;
//    SubWindow* ioWindow = new SubWindow;

    editor = new AsmEditor;
    iopanel = new IOPanel;

    editorWindow->setWindowTitle("Editor");
//    ioWindow->setWindowTitle("Input/Output");

    editorWindow->setWindowIcon(QIcon(":/Resources/icons/editor.png"));
//    ioWindow->setWindowIcon(QIcon(":/Resources/icons/io.png"));

    editorWindow->setWidget(editor);
//    ioWindow->setWidget(iopanel);

//    mdi->addSubWindow(ioWindow);
    mdi->addSubWindow(editorWindow);
}

void MainWindow::createDocks()
{
    this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

    this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    QDockWidget* dockCpuWidget = new QDockWidget("CPU");
    cpuWidget = new CpuWidget;
    dockCpuWidget->setWidget(cpuWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, dockCpuWidget);

    QDockWidget* dockResult = new QDockWidget("Compile Output");
    lstResult = new QListWidget;
    dockResult->setWidget(lstResult);
    this->addDockWidget(Qt::BottomDockWidgetArea, dockResult);

    QDockWidget* dockDRam = new QDockWidget("Data RAM");
    dramWidget = new DataRamWidgetN;
    dockDRam->setWidget(dramWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, dockDRam);

    QDockWidget* dockRom = new QDockWidget("ROM");
    romWidget = new RomWidget;
    dockRom->setWidget(romWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, dockRom);

    QDockWidget* dockPRam = new QDockWidget("Program RAM");
    pramWidget = new ProgramRamWidget;
    dockPRam->setWidget(pramWidget);
    this->addDockWidget(Qt::BottomDockWidgetArea, dockPRam);

    this->tabifyDockWidget(dockResult, dockDRam);
    this->tabifyDockWidget(dockDRam, dockRom);
    this->tabifyDockWidget(dockRom, dockPRam);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowState(Qt::WindowMaximized);

    // create components
    mdi = new QMdiArea;
    mdi->tileSubWindows();
    mdi->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    createDocks();
    createSubWindows();
    createActions();
    createMenu();
    createToolbars();

    statusBar = std::shared_ptr<QStatusBar>(new QStatusBar);

    // set widgets
    this->setCentralWidget(mdi);
    this->setStatusBar(statusBar.get());

    // form settings
    editor->setFocus();
    setWindowTitleFilename();
    this->resize(960, 640);

    // connects
    connect(editor, SIGNAL(textChanged()), this, SLOT(setWindowTitleFilename()));
}

MainWindow::~MainWindow()
{
    delete(mdi);
    delete(cpuWidget);
//    delete(editor); // FIXME delete this pointer, but for now it makes an error and segmentation fault
}

void MainWindow::createOutputFilename()
{
    //    outputname = filename.split("/").last();
    outputname = filename;
    outputname = outputname.split(".").first();
    outputname.append(".bin");
}

void MainWindow::setWindowTitleFilename()
{
    QString title;

    if (editor->document()->isModified())
    {
        title = "*Intel4004";
    }
    else
    {
        title = "Intel4004";
    }
    if (!filename.isEmpty())
    {
        title.append(" - [").append(filename).append("]");
    }
    this->setWindowTitle(title);
}


void MainWindow::readFile()
{
    file.open(filename.toStdString(), ios::in);

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

void MainWindow::writeFile()
{
    file.open(filename.toStdString(), ios::out | ios::trunc);

    if (file.is_open())
    {
        QStringList lines;
        lines = editor->toPlainText().split("\n");

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


void MainWindow::newFile()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, tr("New file"), tr("Do you want to start a new file?"));
    if (btn == QMessageBox::Yes)
    {
        editor->clear();
        filename.clear();

        editor->document()->setModified(false);
        setWindowTitleFilename();

        actCompile->setDisabled(true);
        actRun->setDisabled(true);
        actCompileRun->setDisabled(true);
    }
}

void MainWindow::openFile()
{
    QFileDialog openDlg;
    openDlg.setAcceptMode(QFileDialog::AcceptOpen);

    QString filename = openDlg.getOpenFileName(this, tr("Open File"), "", "Intel4004 assembler (*.asm);;All files (*.*)");
    if (!filename.isEmpty())
    {
        this->filename = filename;
        createOutputFilename();
        readFile();

        editor->document()->setModified(false);
        setWindowTitleFilename();

        actCompile->setDisabled(false);
        actRun->setDisabled(false);
        actCompileRun->setDisabled(false);
    }
}

void MainWindow::saveFile()
{
    if (filename.isEmpty())
    {
        saveAsFile();
    }
    else
    {
        editor->document()->setModified(false);
        writeFile();
    }

    setWindowTitleFilename();
}

void MainWindow::saveAsFile()
{
    QFileDialog saveAsDlg;
    saveAsDlg.setAcceptMode(QFileDialog::AcceptSave);

    QString filename = saveAsDlg.getSaveFileName(this, tr("Save File As"), "", "Intel4004 assembler (*.asm);;All files (*.*)");
    if (!filename.isEmpty())
    {
        this->filename = filename;
        createOutputFilename();
        writeFile();

        editor->document()->setModified(false);
        setWindowTitleFilename();

        actCompile->setDisabled(false);
        actRun->setDisabled(false);
        actCompileRun->setDisabled(false);
    }
}

void MainWindow::exitFile()
{
    QMainWindow::close();
}

void MainWindow::undoEdit()
{
    editor->undo();
}

void MainWindow::redoEdit()
{
    editor->redo();
}

void MainWindow::cutEdit()
{
    editor->cut();
}

void MainWindow::copyEdit()
{
    editor->copy();
}

void MainWindow::pasteEdit()
{
    editor->paste();
}

void MainWindow::deleteEdit()
{
    editor->textCursor().removeSelectedText();
}

void MainWindow::selectAllEdit()
{
    editor->selectAll();
}

void MainWindow::buildCode()
{
    saveFile();
    lstResult->clear();
    compiler.reset(new Compiler(filename.toStdString(), outputname.toStdString()));
    compiler->toCompile();

    for (const Error& i : compiler->getErrors())
    {
        QString e;
        if (i.line != -1)
        {
            e.append("Line ").append(QString::number(i.line));
        }
        e.append("\tCommand: ")
                .append(QString::fromStdString(i.command))
                .append("\t")
                .append(QString::fromStdString(i.text))
                .append("\n");
        lstResult->addItem(e);

    }

    if(compiler->getErrors().empty())
    {
        lstResult->addItem("Project was compiled successfully.\n");

        romWidget->clear();
//        romWidget->write(compiler->getCompiledCode());
    }
}

void MainWindow::compileBuild()
{
    buildCode();
}

void MainWindow::runBuild()
{

}

void MainWindow::compileRunBuild()
{
    buildCode();
    simulator.reset(new Simulator());
    simulator->setCode(compiler->getCompiledCode());
}

void MainWindow::step()
{
    if (simulator)
    {
        simulator->step();
    }
    else
    {
        // TODO Exception
        std::cerr << "Can't make a step, because simulator was not created."  << std::endl;
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, tr("Exit"), tr("Do you want to exit?"));
    if (btn == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}






