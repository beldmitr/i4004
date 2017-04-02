#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <QWidget>
#include <QSyntaxHighlighter>

class Highlighter : public QSyntaxHighlighter
{
public:
    explicit Highlighter(QTextDocument *parent);
    virtual ~Highlighter();
};

#endif // HIGHLIGHTER_H
