#ifndef SYNTAXERROR_H
#define SYNTAXERROR_H

#include <exception>
#include <string>

class SyntaxError : public std::exception {
public:
    explicit SyntaxError(const char* message);

    explicit SyntaxError(const std::string& message)
        : m_message(message)
    {
    }

    virtual ~SyntaxError() noexcept {}

    virtual const char* what() const noexcept;

protected:
    std::string m_message;
};

#endif // SYNTAXERROR_H
