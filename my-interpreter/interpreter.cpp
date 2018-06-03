#include "interpreter.h"
#include "syntaxerror.h"

#include <QDebug>
#include <QVector>

Interpreter::Interpreter(QString text, bool debug)
    : m_debug(debug)
    , m_pos(0)
    , m_text(text)
{
    m_currentChar = m_text.at(m_pos);
    this->debug(QString("Will parse '%1'").arg(m_text));
}

void Interpreter::skipWhitespace()
{
    while (m_currentChar.isSpace()) {
        advance();
    }
}

int Interpreter::integer()
{
    QString result;
    while (m_currentChar.isDigit()) {
        result += m_currentChar;
        advance();
    }
    debug(QString("Found chars in digit: %1").arg(result));
    bool ok;
    int castedResult = result.toInt(&ok);
    debug(QString("Casting ok: %1, with result: %2").arg(ok).arg(castedResult));
    if (!ok) {
        throw new SyntaxError("Syntax error");
    }

    return castedResult;
}

Token Interpreter::getNextToken()
{
    debug("Getting next token ...");
    while (!m_currentChar.isNull()) {
        if (m_currentChar.isSpace()) {
            debug(QString("Skipping spaces"));
            skipWhitespace();
            continue;
        }

        if (m_currentChar.isDigit()) {
            debug(QString("Found digit"));
            return Token(Token::Type::INTEGER, integer());
        }

        if (m_currentChar == '+') {
            debug(QString("Found +"));
            advance();
            return Token(Token::Type::PLUS);
        }

        if (m_currentChar == '-') {
            debug(QString("Found -"));
            advance();
            return Token(Token::Type::MINUS);
        }

        if (m_currentChar == '*') {
            debug(QString("Found *"));
            advance();
            return Token(Token::Type::MULT);
        }

        if (m_currentChar == '/') {
            debug(QString("Found /"));
            advance();
            return Token(Token::Type::DIV);
        }
        debug(QString("Did not find token: %1").arg(m_currentChar));
        QString error = QString("Unexpected token: %1").arg(m_currentChar);
        throw new SyntaxError(error.toLocal8Bit().constData());
    }

    return Token(Token::Type::TEOF);
}

void Interpreter::advance()
{
    m_pos++;
    if (m_pos > m_text.length() - 1) {
        m_currentChar = QChar::Null;
    } else {
        m_currentChar = m_text.at(m_pos);
    }
}

void Interpreter::eat(Token::Type type)
{
    debug(QString("Trying to eat token of type %1").arg(Token::toString(type)));

    if (m_currentToken.type == type) {
        debug("Did eat token.");
        m_currentToken = getNextToken();
        debug(QString("Found new token: %1").arg(Token::toString(m_currentToken.type)));
    } else {
        QString message = QString("Expected token %1, but got %2").arg(Token::toString(type)).arg(Token::toString(m_currentToken.type));
        throw new SyntaxError(message.toLocal8Bit().constData());
    }
}

int Interpreter::term()
{
    Token token = m_currentToken;
    eat(Token::Type::INTEGER);
    return token.value;
}

void Interpreter::debug(QString message)
{
    if (m_debug) {
        qDebug() << message;
    }
}

int Interpreter::expression()
{
    m_currentToken = getNextToken();
    int result = term();
    debug(QString("Result: %1").arg(result));
    QVector<Token::Type> operators = { Token::Type::PLUS, Token::Type::MINUS, Token::Type::MULT, Token::Type::DIV };
    while (operators.contains(m_currentToken.type)) {
        auto token = m_currentToken;
        debug(QString("Token %1 is in list of valid tokens").arg(Token::toString(token.type)));
        if (token.type == Token::Type::PLUS) {
            eat(Token::Type::PLUS);
            result += term();
        } else if (token.type == Token::Type::MINUS) {
            eat(Token::Type::MINUS);
            result -= term();
        } else if (token.type == Token::Type::DIV) {
            eat(Token::Type::DIV);
            result /= term();
        } else if (token.type == Token::Type::MULT) {
            eat(Token::Type::MULT);
            result *= term();
        }
    }
    return result;
}
