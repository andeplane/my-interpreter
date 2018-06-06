#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <QString>

class Lexer {
public:
    Lexer(QString text, bool debug = false);
    Token getNextToken();

protected:
    void advance();
    int integer();
    void skipWhitespace();
    void debug(QString message);

private:
    QString m_text;
    bool m_debug;
    int m_pos;
    QChar m_currentChar;
};

#endif // LEXER_H
