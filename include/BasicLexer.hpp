#pragma once

#include <BasicConsole.hpp>
#include <BasicToken.hpp>
#include <list>
#include <string>

class BasicLexer {
    private:
    std::string remaining;
    int column = 0;
    BasicConsole& console;
    bool err = false;

    public:
    std::list<BasicToken> tokens;
    BasicLexer(BasicConsole& console, const std::string& str) : remaining(str.rbegin(), str.rend()), console(console) {
    }

    inline bool hasError() {
        return this->err;
    }

    inline int next_char() {
        if(this->remaining.empty())
            return -1;

        this->column++;
        char out = this->remaining.back();
        this->remaining.pop_back();
        return out;
    }

    inline void ret_char(char c) {
        if(c == -1)
            return;
        this->column--;
        this->remaining.push_back(c);
    }

    inline bool empty() {
        return this->remaining.empty();
    }

    void run();
    void printErr(char c);
    BasicToken lex_ident(char c);
    BasicToken lex_int_literal(char c);
    BasicToken lex_string_literal();
    void check_keyword(BasicToken& token);
    void check_identifier(BasicToken& token);
};
