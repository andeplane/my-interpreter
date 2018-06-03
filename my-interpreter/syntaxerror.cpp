#include "syntaxerror.h"

SyntaxError::SyntaxError(const char* message)
    : m_message(message)
{
}

const char* SyntaxError::what() const noexcept
{
    return m_message.c_str();
}
