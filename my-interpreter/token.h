#ifndef TOKEN_H
#define TOKEN_H

#include <QString>

class Token {
public:
    enum class Type {
        NONE,
        INTEGER,
        PLUS,
        MINUS,
        MULT,
        DIV,
        TEOF
    };

    Token(Type type = Type::NONE, int value = 0);
    static QString toString(Type type);
    Type type;
    int value;
};

#endif // TOKEN_H
