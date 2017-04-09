#include "editor.h"

Editor::Editor(QWidget *parent) : QWidget(parent)
{
    keywordsInstruction << "NOP" << "JCN" << "FIM" << "SRC" << "FIN" << "JIN" << "JUN" << "JMS"
             << "INC" << "ISZ" << "ADD" << "SUB" << "LD" << "XCH" << "BBL" << "LDM"
             << "WRM" << "WMP" << "WRR" << "WR0" << "WR1" << "WR2" << "WR3" << "SBM"
             << "RDM" << "RDR" << "ADM" << "RD0" << "RD1" << "RD2" << "RD3" << "CLB"
             << "CLC" << "IAC" << "CMC" << "CMA" << "RAL" << "RAR" << "TCC" << "DAC"
             << "TCS" << "STC" << "DAA" << "KBP" << "DCL";
    keywordsPairs << "P0" << "P1" << "P2" << "P3" << "P4" << "P5" << "P6" << "P7";
    keywordsRegisters << "R0" << "R1" << "R2" << "R3" << "R4" << "R5" << "R6" << "R7"
                      << "R8" << "R9" << "R10" << "R11" << "R12" << "R13" << "R14" << "R15";

    layout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout(this));
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    panel = std::shared_ptr<QFrame>(new QFrame);
    edit = std::shared_ptr<QTextEdit>(new QTextEdit);

    // Making minimal size according to screen resolution
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(desktop.primaryScreen());
    edit->setMinimumSize(rect.size() / 4);

    panel->setMinimumWidth(100);
    panel->setCursor(Qt::PointingHandCursor);

    layout->addWidget(panel.get());
    layout->addWidget(edit.get());

    connect(edit.get(), SIGNAL(textChanged()), this, SLOT(highlightKeywords()));
}

Editor::~Editor()
{
    // delete here something or finalize
}

QTextEdit* Editor::getTextEditor()
{
    return edit.get();
}

void Editor::highlightKeywords()
{

}

void Editor::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    // TODO implement here calculating and drawing line numbers
}
