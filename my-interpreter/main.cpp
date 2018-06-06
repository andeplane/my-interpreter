#include "interpreter.h"
#include "syntaxerror.h"
#include <QDebug>
#include <iostream>

int main()
{
    bool debug = false;
    while (true) {
        std::cout << "calc> ";
        std::string input;
        std::getline(std::cin, input); // where input is a std::string
        try {
            auto lexer = std::make_shared<Lexer>(QString::fromStdString(input), debug);
            qDebug() << "Will start parsing now. Ignore what has happened before.";
            Interpreter interpreter(lexer, debug);
            std::cout << interpreter.expression() << std::endl;
        } catch (SyntaxError* error) {
            std::cerr << "Syntax error: " << error->what();
        }
    }
    return 0;
}
