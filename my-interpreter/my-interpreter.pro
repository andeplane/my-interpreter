TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
    token.cpp \
    interpreter.cpp \
    syntaxerror.cpp \
    lexer.cpp

HEADERS += \
    token.h \
    interpreter.h \
    syntaxerror.h \
    lexer.h
