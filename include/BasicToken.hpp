#pragma once

#include <string>

enum class BasicTokenType {
    LET,
    PRINT,
    INPUT,
    IF,
    THEN,
    GOTO,
    GOSUB,
    RETURN,
    REM,
    RUN,
    THEN,
    INT_LITERAL,
    IDENTIFIER,
    ASSIGN,
    COMMA,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LOWER,
    GREATER
};

struct BasicToken {
    BasicTokenType typ;
    std::string sval = "";
    int ival         = 0;

    BasicToken(BasicTokenType typ) : typ(typ) {
    }
};
