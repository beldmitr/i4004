#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <QWidget>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

#include <iostream>

class Highlighter : public QSyntaxHighlighter
{
public:
    explicit Highlighter(QTextDocument *parent);
    virtual ~Highlighter();

    // QSyntaxHighlighter interface
protected:
    void highlightBlock(const QString &text);

private:
    QStringList keywords;

    QString makePattern(const QStringList &list);

    void highlight(const QString &text, QTextCharFormat format, QString pattern, bool caseSensetive);
};

#endif // HIGHLIGHTER_H
