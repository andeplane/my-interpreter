#include "token.h"

Token::Token(Type type, int value)
    : type(type)
    , value(value)
{
}

QString Token::toString(Type type)
{
    if (type == Type::PLUS) {
        return "+";
    }
    if (type == Type::MINUS) {
        return "MINUS";
    }
    if (type == Type::DIV) {
        return "DIV";
    }
    if (type == Type::MULT) {
        return "MULT";
    }
    if (type == Type::INTEGER) {
        return "INT";
    }
    if (type == Type::TEOF) {
        return "EOF";
    }
    if (type == Type::NONE) {
        return "NONE";
    }
    return "NONE";
}
