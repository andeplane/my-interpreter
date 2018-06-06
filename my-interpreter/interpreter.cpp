#include "interpreter.h"
#include "syntaxerror.h"

#include <QDebug>
#include <QVector>

Interpreter::Interpreter(std::shared_ptr<Lexer> lexer, bool debug)
    : m_lexer(lexer)
    , m_debug(debug)
{
    m_currentToken = lexer->getNextToken();
}

void Interpreter::debug(QString message)
{
    if (m_debug) {
        qDebug() << message;
    }
}

void Interpreter::eat(Token::Type type)
{
    debug(QString("EAT: Trying to eat token of type %1").arg(Token::toString(type)));

    if (m_currentToken.type == type) {
        debug("EAT: Did eat token.");
        m_currentToken = m_lexer->getNextToken();
        debug(QString("EAT: Found new token: %1").arg(Token::toString(m_currentToken.type)));
    } else {
        QString message = QString("EAT: Expected token %1, but got %2").arg(Token::toString(type)).arg(Token::toString(m_currentToken.type));
        throw new SyntaxError(message.toLocal8Bit().constData());
    }
}

int Interpreter::factor()
{
    debug(QString("FAC"));
    Token token = m_currentToken;
    debug(QString("FAC: Current token: %1").arg(token.value));
    if (token.type == Token::Type::INTEGER) {
        eat(Token::Type::INTEGER);
        debug(QString("FAC: Found integer %1").arg(token.value));
        return token.value;
    } else if (token.type == Token::Type::LPAREN) {
        eat(Token::Type::LPAREN);
        auto result = expression();
        debug(QString("FAC: Found result in paranthesis %1").arg(result));
        eat(Token::Type::RPAREN);
        return result;
    } else {
        throw new SyntaxError("FAC: Syntax error");
    }
}

int Interpreter::term()
{
    debug(QString("TERM"));
    auto result = factor();
    QVector<Token::Type> operators = { Token::Type::MULT, Token::Type::DIV };
    while (operators.contains(m_currentToken.type)) {
        Token token = m_currentToken;
        if (token.type == Token::Type::MULT) {
            eat(Token::Type::MULT);
            result *= factor();
        } else if (token.type == Token::Type::DIV) {
            eat(Token::Type::DIV);
            result /= factor();
        }
    }

    return result;
}

int Interpreter::expression()
{
    debug(QString("EXP"));
    int result = term();
    debug(QString("EXP: Result: %1").arg(result));
    QVector<Token::Type> operators = { Token::Type::PLUS, Token::Type::MINUS };
    while (operators.contains(m_currentToken.type)) {
        auto token = m_currentToken;
        debug(QString("EXP: Token %1 is in list of valid tokens").arg(Token::toString(token.type)));
        if (token.type == Token::Type::PLUS) {
            eat(Token::Type::PLUS);
            result += term();
        } else if (token.type == Token::Type::MINUS) {
            eat(Token::Type::MINUS);
            result -= term();
        }
    }
    return result;
}
