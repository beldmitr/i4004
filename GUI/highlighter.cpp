#include "highlighter.h"

Highlighter::Highlighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
{
    keywords << "NOP" << "JCN" << "FIM" << "SRC" << "FIN" << "JIN" << "JUN" << "JMS"
             << "INC" << "ISZ" << "ADD" << "SUB" << "LD" << "XCH" << "BBL" << "LDM"
             << "WRM" << "WMP" << "WRR" << "WR0" << "WR1" << "WR2" << "WR3" << "SBM"
             << "RDM" << "RDR" << "ADM" << "RD0" << "RD1" << "RD2" << "RD3" << "CLB"
             << "CLC" << "IAC" << "CMC" << "CMA" << "RAL" << "RAR" << "TCC" << "DAC"
             << "TCS" << "STC" << "DAA" << "KBP" << "DCL";
}

Highlighter::~Highlighter()
{
    // delete here something
}

void Highlighter::highlightBlock(const QString &text)
{
    // Pseudo highliting
    QTextCharFormat formatPseudo;
    formatPseudo.setFontWeight(QFont::Bold);
    formatPseudo.setForeground(Qt::darkBlue);
    QString patternPseudo = "[=*]";
    highlight(text, formatPseudo, patternPseudo, false);

    // Numbers highliting
    QTextCharFormat formatNumbers;
    formatNumbers.setForeground(QColor("#dd5500"));
    QString patternNumbers = QString("")
            .append("\\b(([0-9a-f]+h)")      // 0123456789abcdefh
            .append("|(0x[0-9a-f]+)")    // 0x123456789abcdf
            .append("|(0b[01]+)")     // 0b01
            .append("|([01]+b)")      // 10b
            .append("|([0-9]+))\\b");      // 0123456789
    highlight(text, formatNumbers, patternNumbers, false);

    // Registers highlighting
    QTextCharFormat formatRegisters;
    formatRegisters.setForeground(QColor("#6600cc"));
    QString patternRegisters = "\\b(([Rr]([0-9]|(1[0-5])))|(([0-9]|(1[0-5]))[Rr]))\\b";
    highlight(text, formatRegisters, patternRegisters, false);

    // Pairs highliting
    QTextCharFormat formatPairs;
    formatPairs.setForeground(Qt::blue);
    QString patternPairs = "\\b(([Pp][0-7])|([0-7][Pp]))\\b";
    highlight(text, formatPairs, patternPairs, false);

    // Commands highlighting
    QTextCharFormat formatCommands;
    formatCommands.setFontWeight(QFont::Bold);
    formatCommands.setForeground(Qt::darkBlue);
    QString patternCommands = makePattern(keywords);
    highlight(text, formatCommands, patternCommands, false);

    // Labels highlighting
    QTextCharFormat formatLabels;
    formatLabels.setForeground(Qt::darkYellow);
    QString patternLabels = "^(\\s)*[A-Za-z][A-Za-z0-9]{2,}(,)";
    highlight(text, formatLabels, patternLabels, false);

    // Comments highliting
    QTextCharFormat formatComments;
    formatComments.setForeground(Qt::darkGreen);
    QString patternComments = "/.*";
    highlight(text, formatComments, patternComments, false);
}

QString Highlighter::makePattern(const QStringList &list)
{
    QString pattern;
    if (list.isEmpty())
    {
        return " ";
    }

    for (QString s : list)
    {
        pattern.append("(\\b").append(s).append("\\b)|");
    }
    pattern.remove(pattern.length()-1, 1);  // delete the last | from pattern
    std::cout << pattern.toStdString() << std::endl;
    return pattern;
}

void Highlighter::highlight(const QString &text, QTextCharFormat format, QString pattern, bool caseSensetive)
{
    QRegExp expression(pattern);
    if (!expression.isValid())
    {
        // TODO maybe make GUI exception?
        std::cerr << QString("Pattern is not valid: ").append(pattern).toStdString() << std::endl;
    }
    Qt::CaseSensitivity sensetive = (caseSensetive) ? Qt::CaseSensitive : Qt::CaseInsensitive;
    expression.setCaseSensitivity(sensetive);

    int index = text.indexOf(expression);
    while(index >= 0)
    {
        int length = expression.matchedLength();
        setFormat(index, length, format);
        index = text.indexOf(expression, index + length);
    }
}
