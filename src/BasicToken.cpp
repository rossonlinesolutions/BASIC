#include "BasicToken.hpp"

std::string BasicToken::to_string() const {
    std::string value = basicTokenToString(this->typ);
    value += "{";
    value += this->sval;
    value += ",";
    value += std::to_string(this->ival);
    value += "}";

    return value;
}

std::string basicTokenToString(BasicTokenType typ) {
    switch(typ) {
        case BasicTokenType::LET:
            return "LET";
        case BasicTokenType::PRINT:
            return "PRINT";
        case BasicTokenType::INPUT:
            return "INPUT";
        case BasicTokenType::IF:
            return "IF";
        case BasicTokenType::THEN:
            return "THEN";
        case BasicTokenType::GOTO:
            return "GOTO";
        case BasicTokenType::GOSUB:
            return "GOSUB";
        case BasicTokenType::RETURN:
            return "RETURN";
        case BasicTokenType::REM:
            return "REM";
        case BasicTokenType::RUN:
            return "RUN";
        case BasicTokenType::INT_LITERAL:
            return "INT_LITERAL";
        case BasicTokenType::IDENTIFIER:
            return "IDENTIFIER";
        case BasicTokenType::ASSIGN:
            return "ASSIGN";
        case BasicTokenType::COMMA:
            return "COMMA";
        case BasicTokenType::PLUS:
            return "PLUS";
        case BasicTokenType::MINUS:
            return "MINUS";
        case BasicTokenType::MUL:
            return "MUL";
        case BasicTokenType::DIV:
            return "DIV";
        case BasicTokenType::LOWER:
            return "LOWER";
        case BasicTokenType::GREATER:
            return "GREATER";
        case BasicTokenType::STRING_LITERAL:
            return "STRING_LITERAL";
        default:
            return "UNKNOWN";
    }
}
