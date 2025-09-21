#include <BasicLexer.hpp>
#include <cctype>
#include <iostream>

void BasicLexer::printErr(char c) {
    this->err = true;

    std::string msg = "Lexer error: column " + std::to_string(this->column) + ": Unexpected character `" + c + "`.";
    this->console.printLine(msg);
}

BasicToken BasicLexer::lex_ident(char c) {
    // get identifier
    std::string ident = "";
    ident.push_back(c);

    // insert while next char is upper case letter
    char nxt = this->next_char();
    while(nxt != -1 && isupper(nxt)) {
        ident.push_back(nxt);
        nxt = this->next_char();
    }

    // return last non-upper case letter
    this->ret_char(nxt);

    // create token
    BasicToken token {BasicTokenType::IDENTIFIER};
    token.sval = ident;

    // check if is a keyword
    check_keyword(token);
    if(token.typ != BasicTokenType::IDENTIFIER)
        return token;

    // throw error if is not an identifier ("A" - "Z")
    check_identifier(token);
    return token;
}

BasicToken BasicLexer::lex_int_literal(char c) {
    // get integer
    unsigned long ival = c - '0';

    // insert while next char is number
    char nxt = this->next_char();
    while(nxt != -1 && isdigit(nxt)) {
        ival = ival * 10 + (nxt - '0');
        nxt  = this->next_char();
    }

    // return last non-digit letter
    this->ret_char(nxt);

    // create token
    BasicToken token {BasicTokenType::INT_LITERAL};
    token.ival = ival;
    return token;
}

BasicToken BasicLexer::lex_string_literal() {
    // get string
    std::string value = "";

    // insert until " character
    char nxt = this->next_char();
    while(nxt != '"') {
        // EOF means error
        if(nxt == -1) {
            this->printErr('?');
            break;
        }

        // insert into value
        value.push_back(nxt);
        nxt = this->next_char();
    }

    // Don't return the " character!

    // create token
    BasicToken token {BasicTokenType::STRING_LITERAL};
    token.sval = value;
    return token;
}

void BasicLexer::check_keyword(BasicToken& token) {
    // Convert to uppercase for comparison (BASIC keywords are uppercase)
    const std::string& sval = token.sval;
    if(sval == "LET")
        token.typ = BasicTokenType::LET;
    else if(sval == "PRINT")
        token.typ = BasicTokenType::PRINT;
    else if(sval == "INPUT")
        token.typ = BasicTokenType::INPUT;
    else if(sval == "IF")
        token.typ = BasicTokenType::IF;
    else if(sval == "THEN")
        token.typ = BasicTokenType::THEN;
    else if(sval == "GOTO")
        token.typ = BasicTokenType::GOTO;
    else if(sval == "GOSUB")
        token.typ = BasicTokenType::GOSUB;
    else if(sval == "RETURN")
        token.typ = BasicTokenType::RETURN;
    else if(sval == "REM")
        token.typ = BasicTokenType::REM;
    else if(sval == "RUN")
        token.typ = BasicTokenType::RUN;
}

void BasicLexer::check_identifier(BasicToken& token) {
    if(token.sval.length() == 1 && isupper(token.sval.back()))
        return;

    // error
    this->printErr(token.sval.empty() ? '?' : token.sval.front());
}

void BasicLexer::run() {
    // lex new token while remaining string is not empty
    while(!this->remaining.empty() && !this->err) {

        // identify what to lex on next character
        char nxt = this->next_char();

        // advance whitespace
        while(isspace(nxt)) {
            nxt = this->next_char();
        }

        if(nxt == -1)
            return;

        switch(nxt) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                this->tokens.push_back(this->lex_int_literal(nxt));
                break;
            }
            case '=': {
                this->tokens.push_back(BasicToken {BasicTokenType::ASSIGN});
                break;
            }
            case ',': {
                this->tokens.push_back(BasicToken {BasicTokenType::COMMA});
                break;
            }
            case '+': {
                this->tokens.push_back(BasicToken {BasicTokenType::PLUS});
                break;
            }
            case '-': {
                this->tokens.push_back(BasicToken {BasicTokenType::MINUS});
                break;
            }
            case '*': {
                this->tokens.push_back(BasicToken {BasicTokenType::MUL});
                break;
            }
            case '/': {
                this->tokens.push_back(BasicToken {BasicTokenType::DIV});
                break;
            }
            case '<': {
                this->tokens.push_back(BasicToken {BasicTokenType::LOWER});
                break;
            }
            case '>': {
                this->tokens.push_back(BasicToken {BasicTokenType::GREATER});
                break;
            }
            case '"': {
                this->tokens.push_back(this->lex_string_literal());
                break;
            }
            default: {
                if(isupper(nxt)) {
                    this->tokens.push_back(this->lex_ident(nxt));
                } else {
                    this->printErr(nxt);
                }
            }
        }
    }
}
