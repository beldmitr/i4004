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
#include <fstream>

#include "Compiler/compiler.h"
#include "Simulator/simulator.h"

#include "programramwidget.h"
#include "romwidget.h"
#include "cpuwidget.h"
#include "dataramwidget.h"

#include "editorsubwindow.h"
#include "ledsubwindow.h"
//#include "sevensegmentsubwindow.h"
#include "buttonsubwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    /// TODO Check for undeleted pointers

    QString filename;
    QString outputname;

    std::shared_ptr<QMenuBar> mainMenu;
    std::shared_ptr<QStatusBar> statusBar;

    std::shared_ptr<QMenu> menuFile;
    std::shared_ptr<QMenu> menuEdit;
    std::shared_ptr<QMenu> menuBuild;
    std::shared_ptr<QMenu> menuWindows;

    std::shared_ptr<QMdiArea> mdi;

    std::shared_ptr<EditorSubWindow> editorSubWindow;
    std::shared_ptr<LEDSubWindow> ledSubWindow;
    //    std::shared_ptr<SevenSegmentSubWindow> sevenSegmentSubWindow;
    std::shared_ptr<ButtonSubWindow> buttonSubWindow;

    std::shared_ptr<QToolBar> toolBarFile;
    std::shared_ptr<QToolBar> toolBarEdit;
    std::shared_ptr<QToolBar> toolBarBuild;
    std::shared_ptr<QToolBar> toolBarDebug;
    std::shared_ptr<QToolBar> toolBarMinimize;

    std::shared_ptr<QDockWidget> dockCpuWidget;
    std::shared_ptr<QDockWidget> dockResult;
    std::shared_ptr<QDockWidget> dockDRam;
    std::shared_ptr<QDockWidget> dockRom;
    std::shared_ptr<QDockWidget> dockPRam;

    std::shared_ptr<ProgramRamWidget> pramWidget;
    std::shared_ptr<RomWidget> romWidget;
    std::shared_ptr<CpuWidget> cpuWidget;
    std::shared_ptr<QListWidget> lstResult;
    std::shared_ptr<DataRamWidget> dramWidget;

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

    std::shared_ptr<QAction> actPlay;
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

    Compiler* compiler;   // I do not create this pointer here, so I don't it delete now
    Simulator* simulator; // I do not create this pointer here, so I don't it delete now


    // Methods
    void createActions();
    void createMenu();
    void createToolbars();

//    void readFile();
//    void writeFile();
    void createOutputFilename();

    void createSubWindows();

    void createDocks();

    void buildCode();

    void handleCompile();
    void handleRun();


    
public:
    explicit MainWindow(Compiler &compiler, Simulator& simulator, QWidget *parent = 0);
    virtual ~MainWindow();

signals:
    //    void setWindowTitleFilename();


public slots:
    void closeEvent(QCloseEvent*);

private slots:
    void handleBuildCode();
};

#endif // MAINWINDOW_H
