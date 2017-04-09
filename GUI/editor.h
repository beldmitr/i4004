#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>
#include <QWidget>

#include <QTextEdit>
#include <QFrame>
#include <QHBoxLayout>
#include <QSyntaxHighlighter>

#include <QDesktopWidget>

#include <QStringList>

#include <memory>

class Editor : public QWidget
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);
    virtual ~Editor();

    QTextEdit* getTextEditor();

private:
    std::shared_ptr<QHBoxLayout> layout;
    std::shared_ptr<QFrame> panel;
    std::shared_ptr<QTextEdit> edit;

    QStringList keywordsInstruction;
    QStringList keywordsRegisters;
    QStringList keywordsPairs;

signals:

public slots:
    void highlightKeywords();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // EDITOR_H
