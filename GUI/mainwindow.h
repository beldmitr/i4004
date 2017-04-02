#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QDockWidget>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QTextEdit>
#include <QTabWidget>
#include <QGroupBox>
#include <QAction>
#include <QSizePolicy>
#include <QListWidget>
#include <QMdiArea>
#include <QMdiSubWindow>

#include <QHeaderView>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QAbstractTableModel>

#include <sstream>
#include <iostream>
#include <memory>

#include "asmeditor.h"
#include "editor.h"
#include "programramwidget.h"
#include "romwidget.h"
#include "compiler.h"
#include "cpuwidget.h"
#include "subwindow.h"
#include "dataramwidgetn.h"
#include "error.h"
#include "simulator.h"

#include "ledpanel.h"
#include "sevensegmentpanel.h"
#include "buttonpanel.h"

#include "editorsubwindow.h"
#include "ledsubwindow.h"
#include "sevensegmentsubwindow.h"
#include "buttonsubwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    // FIXME What about delete these pointers, man, or make them smart?
    std::shared_ptr<Compiler> compiler;
    std::shared_ptr<Simulator> simulator;

    QString filename;
    QString outputname;

    std::shared_ptr<QMenuBar> mainMenu;
    std::shared_ptr<QStatusBar> statusBar;

    std::shared_ptr<QMenu> menuFile;
    std::shared_ptr<QMenu> menuEdit;
    std::shared_ptr<QMenu> menuBuild;
    std::shared_ptr<QMenu> menuWindows;

    std::shared_ptr<EditorSubWindow> editorSubWindow;
    std::shared_ptr<LEDSubWindow> ledSubWindow;
    std::shared_ptr<SevenSegmentSubWindow> sevenSegmentSubWindow;
    std::shared_ptr<ButtonSubWindow> buttonSubWindow;

    QMdiArea* mdi; // TODO make smart ptr, for now it doesn't work, program crashes after exiting
    AsmEditor* editor; // TODO make smart ptr, for now it doesn't work, program crashes after exiting

    std::shared_ptr<QToolBar> toolBarFile;
    std::shared_ptr<QToolBar> toolBarEdit;
    std::shared_ptr<QToolBar> toolBarBuild;
    std::shared_ptr<QToolBar> toolBarDebug;
    std::shared_ptr<QToolBar> toolBarMinimize;

    ProgramRamWidget* pramWidget; // TODO make smart ptr, for now it doesn't work, program crashes after exiting
    RomWidget* romWidget; // TODO make smart ptr, for now it doesn't work, program crashes after exiting
    CpuWidget* cpuWidget; // TODO make smart ptr, for now it doesn't work, program crashes after exiting
    QListWidget* lstResult; // TODO make smart ptr, for now it doesn't work, program crashes after exiting
    DataRamWidgetN* dramWidget; // TODO make smart ptr, for now it doesn't work, program crashes after exiting

    std::shared_ptr<QDockWidget> dockCpuWidget;
    std::shared_ptr<QDockWidget> dockResult;
    std::shared_ptr<QDockWidget> dockDRam;
    std::shared_ptr<QDockWidget> dockRom;
    std::shared_ptr<QDockWidget> dockPRam;

    std::shared_ptr<QAction> actNew;
    std::shared_ptr<QAction> actOpen;
    std::shared_ptr<QAction> actSave;
    std::shared_ptr<QAction> actSaveAs;
    std::shared_ptr<QAction> actExit;

    std::shared_ptr<QAction> actUndo;
    std::shared_ptr<QAction> actRedo;
    std::shared_ptr<QAction> actCut;
    std::shared_ptr<QAction> actCopy;
    std::shared_ptr<QAction> actPaste;
    std::shared_ptr<QAction> actDelete;
    std::shared_ptr<QAction> actSelectAll;

    std::shared_ptr<QAction> actCompile;
    std::shared_ptr<QAction> actRun;
    std::shared_ptr<QAction> actCompileRun;

    std::shared_ptr<QAction> actResume;
    std::shared_ptr<QAction> actStep;
    std::shared_ptr<QAction> actStop;
    std::shared_ptr<QAction> actReset;

    std::shared_ptr<QAction> nextWindow;
    std::shared_ptr<QAction> prevWindow;
    std::shared_ptr<QAction> minimizeAll;
    std::shared_ptr<QAction> showWindows;

    /*
     * This is list of buttons, in Windows in main menu, like Input/Output or Editor.
     * They are created dynamically in a function and must be deleted at the end.
     * So they are in this vector and are deleted after in deconstructor
     */
    std::vector<QAction*> listWindowsMenuBtn;

    /*
     * This is list of buttons with windows in a toolbar, like Input/Output or Editor.
     * They are created dynamically in a function and must be deleted at the end.
     * So they are in this vector and are deleted after in deconstructor
     */
    std::vector<QAction*> listWindowsToolbarBtn;

    fstream file;

    // Methods
    void createActions();
    void createMenu();
    void createToolbars();

    void readFile();
    void writeFile();
    void createOutputFilename();

    void createSubWindows();

    void createDocks();

    void buildCode();
    
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

signals:

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void exitFile();

    void undoEdit();
    void redoEdit();
    void cutEdit();
    void copyEdit();
    void pasteEdit();
    void deleteEdit();
    void selectAllEdit();

    void compileBuild();
    void runBuild();
    void compileRunBuild();

    void debugResume();
    void debugStep();
    void debugStop();
    void debugReset();

    void setWindowTitleFilename();


public slots:
    void closeEvent(QCloseEvent*);
};

#endif // MAINWINDOW_H
