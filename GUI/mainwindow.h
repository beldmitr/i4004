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
#include "programramwidget.h"
#include "dataramwidget.h"
#include "romwidget.h"
#include "compiler.h"
#include "cpuwidget.h"
#include "iopanel.h"
#include "subwindow.h"
#include "dataramwidgetn.h"
#include "error.h"
#include "simulator.h"

//#include "processorwidget.h"

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
    std::shared_ptr<AsmEditor> editor;
    QMdiArea* mdi; // TODO make smart ptr, for now it doesn't work, program crashes after exiting
    std::shared_ptr<QStatusBar> statusBar;

    std::shared_ptr<QToolBar> toolBarFile;
    std::shared_ptr<QToolBar> toolBarEdit;
    std::shared_ptr<QToolBar> toolBarBuild;
    std::shared_ptr<QToolBar> toolBarDebug;
    std::shared_ptr<QToolBar> toolBarMinimize;

//    QDockWidget* dockProcessor;
//    QDockWidget* dockRom;
//    QDockWidget* dockPRam;
//    QDockWidget* dockDRam;
//    QDockWidget* dockResults;
//    QDockWidget* dockIO;

    ProgramRamWidget* pramWidget;
    RomWidget* romWidget;
//    ProcessorWidget* cpuWidget;
//    QTabWidget* tabDRam;
    CpuWidget* cpuWidget;
    QListWidget* lstResult;
    DataRamWidgetN* dramWidget;
    IOPanel* iopanel;

    QAction* actNew;
    QAction* actOpen;
    QAction* actSave;
    QAction* actSaveAs;
    QAction* actExit;

    QAction* actUndo;
    QAction* actRedo;
    QAction* actCut;
    QAction* actCopy;
    QAction* actPaste;
    QAction* actDelete;
    QAction* actSelectAll;

    QAction* actCompile;
    QAction* actRun;
    QAction* actCompileRun;

    QAction* actStep;

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
    ~MainWindow();

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

    void step();

    void setWindowTitleFilename();


public slots:
    void closeEvent(QCloseEvent*);
};

#endif // MAINWINDOW_H
