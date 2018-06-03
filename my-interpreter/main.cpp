#include "interpreter.h"
#include "syntaxerror.h"
#include <iostream>

int main()
{
    bool debug = false;
    while (true) {
        std::cout << "calc> ";
        std::string input;
        std::getline(std::cin, input); // where input is a std::string
        try {
            Interpreter interpreter(QString::fromStdString(input), debug);
            std::cout << interpreter.expression() << std::endl;
        } catch (SyntaxError* error) {
            std::cerr << "Syntax error: " << error->what();
        }
    }
    return 0;
}
