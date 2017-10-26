#ifndef EDITOR_H
#define EDITOR_H

#include <QObject>
#include <QTextEdit>
#include <QAbstractItemView>
#include <QCompleter>
#include <QScrollBar>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QToolTip>

#include <memory>

#include "highlighter.h"

class Editor : public QTextEdit
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);
    virtual ~Editor();

private:
    const int tabStop = 4;  // tab characters

    std::shared_ptr<Highlighter> highliter;
    std::shared_ptr<QCompleter> completer;

    QString textUnderCursor() const;
    QStringList fileToList(const QString& filename) const;

private slots:
    void insertCompletion(const QString& completion);


    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
};

#endif // EDITOR_H
