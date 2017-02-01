#include "asmeditor.h"

/*
 *
 * Editor class
 *
 */

AsmEditor::AsmEditor(QWidget *parent) : QTextEdit(parent)
{
//    QTextFrame* frame = this->document()->rootFrame();
//    QTextFrameFormat f;

//    f.setLeftMargin(50);
//    f.setTopMargin(5);
//    f.setRightMargin(10);
//    f.setBottomMargin(5);

//    frame->setFrameFormat(f);
//    this->setGeometry(60,0, this->width(), this->height());

}

AsmEditor::~AsmEditor()
{
    // delete or finalize here something
}


void AsmEditor::paintEvent(QPaintEvent* e)
{

    QTextEdit::paintEvent(e);

    // Left panel
//    QPainter p(viewport());
//    p.setRenderHint(QPainter::Antialiasing, true);
//    p.setPen(QPen("gray"));
//    p.setBrush(QBrush(Qt::lightGray, Qt::SolidPattern));

//    p.drawRect(0, 0, 40, this->height());

    // Line numbers
//    QTextBlock block = firstVisibleBlock();
//    int blockNumber = block.blockNumber();
//    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
//    int bottom = top + (int) blockBoundingRect(block).height();

//    while (block.isValid() && top <= e->rect().bottom()) {
//        if (block.isVisible() && bottom >= e->rect().top()) {
//            QString number = QString::number(blockNumber + 1);
//            p.setPen(Qt::black);
//            p.drawText(0, top, 40, fontMetrics().height(),
//                       Qt::AlignRight, number);
//        }

//        block = block.next();
//        top = bottom;
//        bottom = top + (int) blockBoundingRect(block).height();
//        ++blockNumber;
//    }

}




