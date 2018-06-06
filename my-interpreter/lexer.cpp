#include "lexer.h"
#include "syntaxerror.h"

#include <QDebug>

Lexer::Lexer(QString text, bool debug)
    : m_text(text)
    , m_debug(debug)
    , m_pos(0)
{
    m_currentChar = text[m_pos];
    this->debug(QString("Will parse '%1'").arg(m_text));
}

void Lexer::debug(QString message)
{
    if (m_debug) {
        qDebug() << message;
    }
}

void Lexer::skipWhitespace()
{
    while (m_currentChar.isSpace()) {
        advance();
    }
}

int Lexer::integer()
{
    debug(QString("INT"));
    QString result;
    while (m_currentChar.isDigit()) {
        result += m_currentChar;
        advance();
    }
    debug(QString("INT: Found chars in digit: %1").arg(result));
    bool ok;
    int castedResult = result.toInt(&ok);
    debug(QString("INT: Casting ok: %1, with result: %2").arg(ok).arg(castedResult));
    if (!ok) {
        throw new SyntaxError("INT: Syntax error");
    }

    return castedResult;
}

Token Lexer::getNextToken()
{
    debug(QString("GNT %1 at %2").arg(long(this)).arg(m_pos));
    while (!m_currentChar.isNull()) {
        if (m_currentChar.isSpace()) {
            debug(QString("GNT: Skipping spaces"));
            skipWhitespace();
            continue;
        }

        if (m_currentChar.isDigit()) {
            debug(QString("GNT: Found digit"));
            return Token(Token::Type::INTEGER, integer());
        }

        if (m_currentChar == '+') {
            debug(QString("GNT: Found +"));
            advance();
            return Token(Token::Type::PLUS);
        }

        if (m_currentChar == '(') {
            debug(QString("GNT: Found ("));
            advance();
            return Token(Token::Type::LPAREN);
        }

        if (m_currentChar == ')') {
            debug(QString("GNT: Found )"));
            advance();
            return Token(Token::Type::RPAREN);
        }

        if (m_currentChar == '-') {
            debug(QString("GNT: Found -"));
            advance();
            return Token(Token::Type::MINUS);
        }

        if (m_currentChar == '*') {
            debug(QString("GNT: Found *"));
            advance();
            return Token(Token::Type::MULT);
        }

        if (m_currentChar == '/') {
            debug(QString("GNT: Found /"));
            advance();
            return Token(Token::Type::DIV);
        }
        debug(QString("GNT: Did not find token: %1").arg(m_currentChar));
        QString error = QString("GNT: Unexpected token: %1").arg(m_currentChar);
        throw new SyntaxError(error.toLocal8Bit().constData());
    }

    return Token(Token::Type::TEOF);
}

void Lexer::advance()
{
    m_pos++;
    debug(QString("ADVANCE to %1").arg(m_pos));
    if (m_pos > m_text.length() - 1) {
        m_currentChar = QChar::Null;
    } else {
        m_currentChar = m_text.at(m_pos);
    }
}
