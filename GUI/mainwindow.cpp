#include "mainwindow.h"

void MainWindow::createActions()
{
    // Actions File
    actNew = std::shared_ptr<QAction>(new QAction(tr("&New"), this));
    actNew->setIcon(QIcon(":/Resources/icons/new.png"));
    actNew->setShortcut(QKeySequence::New);
    connect(actNew.get(), &QAction::triggered, [=](){
        this->editorSubWindow->newFile();
    });

    actOpen = std::shared_ptr<QAction>(new QAction(tr("&Open"), this));
    actOpen->setIcon(QIcon(":/Resources/icons/open.png"));
    actOpen->setShortcut(QKeySequence::Open);
    connect(actOpen.get(), &QAction::triggered, this, [=](){
        this->editorSubWindow->openFile();
    });

    actSave = std::shared_ptr<QAction>(new QAction(tr("&Save"), this));
    actSave->setIcon(QIcon(":/Resources/icons/save.png"));
    actSave->setShortcut(QKeySequence::Save);
    connect(actSave.get(), &QAction::triggered, [=](){
        this->editorSubWindow->saveFile();
    });

    actSaveAs = std::shared_ptr<QAction>(new QAction(tr("Save As..."), this));
    actSaveAs->setIcon(QIcon(":/Resources/icons/saveas.png"));
    actSaveAs->setShortcut(QKeySequence::SaveAs);
    connect(actSaveAs.get(), &QAction::triggered, [=](){
        this->editorSubWindow->saveAsFile();
    });

    actExit = std::shared_ptr<QAction>(new QAction(tr("E&xit"), this));
    actExit->setIcon(QIcon(":/Resources/icons/exit.png"));
    actExit->setShortcut(tr("Ctrl+Q"));
    connect(actExit.get(), &QAction::triggered, [=](){
        QMainWindow::close();
    });

    // Actions Edit
    actUndo = std::shared_ptr<QAction>(new QAction(tr("Undo"), this));
    actUndo->setIcon(QIcon(":/Resources/icons/undo.png"));
    actUndo->setShortcut(QKeySequence::Undo);
    connect(actUndo.get(), &QAction::triggered, [=](){
        this->editorSubWindow->undoEdit();
    });

    actRedo = std::shared_ptr<QAction>(new QAction(tr("Redo"), this));
    actRedo->setIcon(QIcon(":/Resources/icons/redo.png"));
    actRedo->setShortcut(QKeySequence::Redo);
    connect(actRedo.get(), &QAction::triggered, [=](){
        this->editorSubWindow->redoEdit();
    });

    actCut = std::shared_ptr<QAction>(new QAction(tr("Cut"), this));
    actCut->setIcon(QIcon(":/Resources/icons/cut.png"));
    actCut->setShortcut(QKeySequence::Cut);
    connect(actCut.get(), &QAction::triggered, [=](){
        this->editorSubWindow->cutEdit();
    });

    actCopy = std::shared_ptr<QAction>(new QAction(tr("Copy"), this));
    actCopy->setIcon(QIcon(":/Resources/icons/copy.png"));
    actCopy->setShortcut(QKeySequence::Copy);
    connect(actCopy.get(), &QAction::triggered, [=](){
        this->editorSubWindow->copyEdit();
    });

    actPaste = std::shared_ptr<QAction>(new QAction(tr("Paste"), this));
    actPaste->setIcon(QIcon(":/Resources/icons/paste.png"));
    actPaste->setShortcut(QKeySequence::Paste);
    connect(actPaste.get(), &QAction::triggered, [=](){
        this->editorSubWindow->pasteEdit();
    });

    actDelete = std::shared_ptr<QAction>(new QAction(tr("Delete"), this));
    actDelete->setIcon(QIcon(":/Resources/icons/delete.png"));
    actDelete->setShortcut(QKeySequence::Delete);
    connect(actDelete.get(), &QAction::triggered, [=](){
        this->editorSubWindow->deleteEdit();
    });

    actSelectAll = std::shared_ptr<QAction>(new QAction(tr("Select All"), this));
    actSelectAll->setIcon(QIcon(":/Resources/icons/selectall.png"));
    actSelectAll->setShortcut(QKeySequence::SelectAll);
    connect(actSelectAll.get(), &QAction::triggered, [=](){
        this->editorSubWindow->selectAllEdit();
    });

    // Actions Build
    actCompile = std::shared_ptr<QAction>(new QAction(tr("Compile"), this));
    actCompile->setIcon(QIcon(":/Resources/icons/compile.png"));
    actCompile->setShortcut(tr("Ctrl+B"));

    connect(actCompile.get(), &QAction::triggered, [=](){
        buildCode();

    });

    // Actions Debug
    actPlay = std::shared_ptr<QAction>(new QAction(tr("Play"), this));
    actPlay->setIcon(QIcon(":/Resources/icons/debug_resume.png"));
    actPlay->setShortcut(tr("F5"));
    connect(actPlay.get(), &QAction::triggered, [=](){
        simulator->play();
    });

    actStep = std::shared_ptr<QAction>(new QAction(tr("Step"), this));
    actStep->setIcon(QIcon(":/Resources/icons/debug_step_over.png"));
    actStep->setShortcut(tr("F10"));
    connect(actStep.get(), &QAction::triggered, [=](){
        simulator->step();
    });

    actStop = std::shared_ptr<QAction>(new QAction(tr("Stop"), this));
    actStop->setIcon(QIcon(":/Resources/icons/debug_stop.png"));
    connect(actStop.get(), &QAction::triggered, [=](){
        simulator->stop();
    });

    actReset = std::shared_ptr<QAction>(new QAction(tr("Reset"), this));
    actReset->setIcon(QIcon(":/Resources/icons/debug_restart.png"));
    connect(actReset.get(), &QAction::triggered, [=](){
        simulator->reset();
    });
}

void MainWindow::createMenu()
{
    // Create main menu
    mainMenu = std::shared_ptr<QMenuBar>(new QMenuBar);
    this->setMenuBar(mainMenu.get());

    // Create menu File
    menuFile = std::shared_ptr<QMenu>(mainMenu->addMenu("File"));
    menuFile->addAction(actNew.get());
    menuFile->addAction(actOpen.get());
    menuFile->addSeparator();
    menuFile->addAction(actSave.get());
    menuFile->addAction(actSaveAs.get());
    menuFile->addSeparator();
    menuFile->addAction(actExit.get());

    // Create menu Edit
    menuEdit = std::shared_ptr<QMenu>(mainMenu->addMenu("Edit"));
    menuEdit->addAction(actUndo.get());
    menuEdit->addAction(actRedo.get());
    menuEdit->addSeparator();
    menuEdit->addAction(actCut.get());
    menuEdit->addAction(actCopy.get());
    menuEdit->addAction(actPaste.get());
    menuEdit->addAction(actDelete.get());
    menuEdit->addSeparator();
    menuEdit->addAction(actSelectAll.get());

    // Create menu Build
    menuBuild = std::shared_ptr<QMenu>(mainMenu->addMenu("Build"));
    menuBuild->addAction(actCompile.get());
    menuBuild->addSeparator();

    // Create menu Preferences
    mainMenu->addMenu("Preferences");

    // Create menu Windows
    menuWindows = std::shared_ptr<QMenu>(mainMenu->addMenu("Windows"));
    nextWindow = std::shared_ptr<QAction>(new QAction("Next window", this));
    connect(nextWindow.get(), SIGNAL(triggered(bool)), mdi.get(), SLOT(activateNextSubWindow()));
    menuWindows->addAction(nextWindow.get());

    prevWindow = std::shared_ptr<QAction>(new QAction("Previous window", this));
    connect(prevWindow.get(), SIGNAL(triggered(bool)), mdi.get(), SLOT(activatePreviousSubWindow()));
    menuWindows->addAction(prevWindow.get());

    menuWindows->addSeparator();

    for(QMdiSubWindow* w : mdi->subWindowList())
    {
        QAction* act = new QAction(w->windowTitle(), this);
        listWindowsMenuBtn.push_back(act);
        connect(act, SIGNAL(triggered(bool)), w, SLOT(show()));
        connect(act, SIGNAL(triggered(bool)), w, SLOT(setFocus()));
        menuWindows->addAction(act);
    }

    menuWindows->addSeparator();

    minimizeAll = std::shared_ptr<QAction>(new QAction("Minimize all", this));
    for(QMdiSubWindow* w : mdi->subWindowList())
    {
        connect(minimizeAll.get(), SIGNAL(triggered(bool)), w, SLOT(showMinimized()));
    }
    menuWindows->addAction(minimizeAll.get());

    showWindows = std::shared_ptr<QAction>(new QAction("Show windows", this));
    for(QMdiSubWindow* w : mdi->subWindowList())
    {
        connect(showWindows.get(), SIGNAL(triggered(bool)), w, SLOT(showNormal()));
    }
    connect(showWindows.get(), SIGNAL(triggered(bool)), mdi.get(), SLOT(tileSubWindows()));

    menuWindows->addAction(showWindows.get());

    // Create menu Help
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
        listWindowsToolbarBtn.push_back(act);
        act->setToolTip("Show " + title);

        connect(act, SIGNAL(triggered(bool)), w, SLOT(show()));
        connect(act, SIGNAL(triggered(bool)), w, SLOT(setFocus()));

        toolBarMinimize->addAction(act);
    }

    toolBarMinimize->setFloatable(false);
    toolBarMinimize->setMovable(false);

    toolBarFile = std::shared_ptr<QToolBar>(new QToolBar("File"));
    toolBarFile->addAction(actNew.get());
    toolBarFile->addAction(actOpen.get());
    toolBarFile->addAction(actSave.get());

    toolBarEdit = std::shared_ptr<QToolBar>(new QToolBar("Edit"));
    toolBarEdit->addAction(actUndo.get());
    toolBarEdit->addAction(actRedo.get());
    toolBarEdit->addSeparator();
    toolBarEdit->addAction(actCut.get());
    toolBarEdit->addAction(actCopy.get());
    toolBarEdit->addAction(actPaste.get());
    toolBarEdit->addAction(actDelete.get());
    toolBarEdit->addSeparator();
    toolBarEdit->addAction(actSelectAll.get());

    toolBarBuild = std::shared_ptr<QToolBar>(new QToolBar("Build"));
    toolBarBuild->addAction(actCompile.get());

    toolBarDebug = std::shared_ptr<QToolBar>(new QToolBar("Debug"));
    toolBarDebug->addAction(actPlay.get());
    toolBarDebug->addAction(actStop.get());
    toolBarDebug->addAction(actStep.get());
    toolBarDebug->addAction(actReset.get());

    this->addToolBar(toolBarFile.get());
    this->addToolBar(toolBarEdit.get());
    this->addToolBar(toolBarBuild.get());
    this->addToolBar(toolBarDebug.get());
    this->addToolBar(Qt::LeftToolBarArea, toolBarMinimize.get());
}

void MainWindow::createSubWindows()
{
    editorSubWindow = std::shared_ptr<EditorSubWindow>(new EditorSubWindow(this));
    ledSubWindow = std::shared_ptr<LEDSubWindow>(new LEDSubWindow(simulator));
    //    sevenSegmentSubWindow = std::shared_ptr<SevenSegmentSubWindow>(new SevenSegmentSubWindow);
    buttonSubWindow = std::shared_ptr<ButtonSubWindow>(new ButtonSubWindow(simulator));

    mdi->addSubWindow(editorSubWindow.get());
    mdi->addSubWindow(ledSubWindow.get());
    //    mdi->addSubWindow(sevenSegmentSubWindow.get());
    mdi->addSubWindow(buttonSubWindow.get());
}

void MainWindow::createDocks()
{
    this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

    this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    dockResult = std::shared_ptr<QDockWidget>(new QDockWidget("Compile Output"));
    lstResult = std::shared_ptr<QListWidget>(new QListWidget);
    dockResult->setWidget(lstResult.get());
    this->addDockWidget(Qt::BottomDockWidgetArea, dockResult.get());
    dockResult->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    dockDRam = std::shared_ptr<QDockWidget>(new QDockWidget("Data RAM"));
    dramWidget = std::shared_ptr<DataRamWidget>(new DataRamWidget(simulator));
    dockDRam->setWidget(dramWidget.get());
    this->addDockWidget(Qt::BottomDockWidgetArea, dockDRam.get());
    dockDRam->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    dockRom = std::shared_ptr<QDockWidget>(new QDockWidget("ROM"));
    romWidget = std::shared_ptr<RomWidget>(new RomWidget(simulator));
    dockRom->setWidget(romWidget.get());
    this->addDockWidget(Qt::BottomDockWidgetArea, dockRom.get());
    dockRom->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    dockPRam = std::shared_ptr<QDockWidget>(new QDockWidget("Program RAM"));
    pramWidget = std::shared_ptr<ProgramRamWidget>(new ProgramRamWidget(simulator));
    dockPRam->setWidget(pramWidget.get());
    this->addDockWidget(Qt::BottomDockWidgetArea, dockPRam.get());
    dockPRam->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    this->tabifyDockWidget(dockRom.get(), dockDRam.get());
    this->tabifyDockWidget(dockDRam.get(), dockPRam.get());
    this->tabifyDockWidget(dockPRam.get(), dockResult.get());

    dockCpuWidget = std::shared_ptr<QDockWidget>(new QDockWidget("CPU"));
    cpuWidget = std::shared_ptr<CpuWidget>(new CpuWidget(simulator));
    dockCpuWidget->setWidget(cpuWidget.get());
    this->addDockWidget(Qt::BottomDockWidgetArea, dockCpuWidget.get());
//    cpuWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    dockCpuWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


//    QSizePolicy sizePolicy = dockCpuWidget->sizePolicy();
//    sizePolicy.setHorizontalPolicy(QSizePolicy::Maximum);
//    dockCpuWidget->setSizePolicy(sizePolicy);

//    sizePolicy = dockResult->sizePolicy();
//    sizePolicy.setHorizontalPolicy(QSizePolicy::Minimum);
//    dockResult->setSizePolicy(sizePolicy);

//    sizePolicy = dockDRam->sizePolicy();
//    sizePolicy.setHorizontalPolicy(QSizePolicy::Minimum);
//    dockDRam->setSizePolicy(sizePolicy);

//    sizePolicy = dockRom->sizePolicy();
//    sizePolicy.setHorizontalPolicy(QSizePolicy::Minimum);
//    dockRom->setSizePolicy(sizePolicy);

//    sizePolicy = dockPRam->sizePolicy();
//    sizePolicy.setHorizontalPolicy(QSizePolicy::Minimum);
//    dockPRam->setSizePolicy(sizePolicy);
}

MainWindow::MainWindow(Compiler& compiler, Simulator &simulator, QWidget *parent)
    : QMainWindow(parent)
{
    this->compiler = &compiler;
    this->simulator = &simulator;

    this->setWindowState(Qt::WindowMaximized);

    // create components
    mdi = std::shared_ptr<QMdiArea>(new QMdiArea);
//    mdi->tileSubWindows();
    mdi->cascadeSubWindows();

    mdi->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    createActions();
    createDocks();
    createSubWindows();
    createToolbars();
    createMenu();

    statusBar = std::shared_ptr<QStatusBar>(new QStatusBar);

    // set widgets
    this->setCentralWidget(mdi.get());
    this->setStatusBar(statusBar.get());

    // form settings
    //    QTextEdit* textEditor = this->editorSubWindow->getTextEditor();
    //    textEditor->setFocus();
    //    setWindowTitleFilename();
    //    this->resize(960, 640);

    //    // connects
    //    connect(textEditor, SIGNAL(textChanged()), this, SLOT(setWindowTitleFilename()));

    connect(this->compiler, SIGNAL(onCompiled()), this, SLOT(handleBuildCode()));

}

MainWindow::~MainWindow()
{
    for (QAction* a : listWindowsMenuBtn)
    {
        delete(a);
    }

    for (QAction* a : listWindowsToolbarBtn)
    {
        delete(a);
    }
}

void MainWindow::createOutputFilename()
{
    //    outputname = filename.split("/").last();
    outputname = filename;
    outputname = outputname.split(".").first();
    outputname.append(".bin");
}

//void MainWindow::setWindowTitleFilename()
//{
//    QString title = "Intel4004";
////    QTextEdit* textEditor = this->editorSubWindow->getTextEditor();

////    if (textEditor->document()->isModified())
////    {
////        title = "*Intel4004";
////    }
////    else
////    {
////        title = "Intel4004";
////    }
////    if (!filename.isEmpty())
////    {
////        title.append(" - [").append(filename).append("]");
////    }
//    this->setWindowTitle(title);
//}





void MainWindow::buildCode()
{
    this->actCompile->setDisabled(true);




    this->editorSubWindow->saveFile();

    lstResult->clear();

    filename = this->editorSubWindow->getFilename();

    QtConcurrent::run([=](){
       compiler->compile(filename.toStdString());
    });

//    QThread* thr = new QThread;
//    connect(thr, SIGNAL(started()), this, SLOT(compile()));
//    thr->start();
}

void MainWindow::handleCompile()
{
    buildCode();
}

void MainWindow::handleRun()
{
    simulator->play();
}

//void MainWindow::compileRunBuild()
//{
//    buildCode();
////    simulator.reset(new Simulator());
////    simulator->setCode(compiler->getCompiledCode());
//}



void MainWindow::closeEvent(QCloseEvent* event)
{
    this->simulator->stop();
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, tr("Exit"), tr("Do you want to exit?"));
    if (btn == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
        this->simulator->play();
    }
}

void MainWindow::handleBuildCode()
{
    std::vector<std::shared_ptr<CompilerError>> errors = this->compiler->getErrors();

    if (errors.empty())
    {
        lstResult->addItem(QString(tr("Compiled successfully")));
    }
    else
    {
        for (const std::shared_ptr<CompilerError> e : errors)
        {
            QString msg;
            //            if (e.row != -1)
            //            {
            msg.append("Line ").append(QString::number(e->row));
            //            }
            msg.append(": ")
                    .append(QString(e->message.c_str()));
            lstResult->addItem(msg);
        }
    }

    this->actCompile->setDisabled(false);

    return;
}







