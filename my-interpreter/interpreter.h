#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "lexer.h"
#include "token.h"
#include <QString>
#include <memory>

class Interpreter {
public:
    Interpreter(std::shared_ptr<Lexer> lexer, bool debug = false);
    int expression();

protected:
    void eat(Token::Type type);
    int term();
    int factor();
    void debug(QString message);

private:
    std::shared_ptr<Lexer> m_lexer;
    bool m_debug;
    Token m_currentToken;
};

#endif // INTERPRETER_H
