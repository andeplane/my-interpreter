#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "token.h"
#include <QString>

class Interpreter {
public:
    Interpreter(QString text, bool debug = false);
    int expression();
    bool m_debug;

protected:
    void skipWhitespace();
    Token getNextToken();
    void advance();
    void eat(Token::Type type);
    int integer();
    int term();
    void debug(QString message);

private:
    uint64_t m_pos;
    QString m_text;
    QChar m_currentChar;
    Token m_currentToken;
};

#endif // INTERPRETER_H
