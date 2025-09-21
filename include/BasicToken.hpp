#pragma once

#include <string>

enum class BasicTokenType {
    LET,
    PRINT,
    INPUT,
    IF,
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
    GREATER,
    STRING_LITERAL
};

extern std::string basicTokenToString(BasicTokenType typ);

struct BasicToken {
    BasicTokenType typ;
    std::string sval       = "";
    unsigned long int ival = 0;

    BasicToken(BasicTokenType typ) : typ(typ) {
    }
    std::string to_string() const;
};
