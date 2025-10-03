#include <BasicEndStatement.hpp>
#include <BasicGoSubStatement.hpp>
#include <BasicGotoStatement.hpp>
#include <BasicIfStatement.hpp>
#include <BasicInputStatement.hpp>
#include <BasicIntExpression.hpp>
#include <BasicLetStatement.hpp>
#include <BasicParser.hpp>
#include <BasicPrintStatement.hpp>
#include <BasicReturnStatement.hpp>
#include <BasicRunStatement.hpp>
#include <BasicUnaryExpression.hpp>
#include <BasicVarExpression.hpp>
#include <memory>
#include <string>

std::unique_ptr<BasicStatement> BasicParser::parseLine(BasicConsole& console, BasicTokenList& ts) const {
    auto stmt = this->parseStatement(console, ts);

    if(!ts.empty()) {
        console.printLine("Error: found unparsed junk at end.");
        return nullptr;
    }

    return stmt;
}

BasicOperation BasicParser::parseOp(BasicConsole& console, BasicTokenList& ts, int lprec) const {
    if(ts.empty())
        return std::nullopt;

    BasicOperation op;

    // return binary operator with precedences
    switch(ts.front().typ) {
        case BasicTokenType::PLUS: {
            op = std::optional<std::tuple<BasicBinOp, int, int>> {{BasicBinOp::PLUS, 1, 2}};
            break;
        }
        case BasicTokenType::MINUS: {
            op = std::optional<std::tuple<BasicBinOp, int, int>> {{BasicBinOp::MINUS, 1, 2}};
            break;
        }
        case BasicTokenType::MUL: {
            op = std::optional<std::tuple<BasicBinOp, int, int>> {{BasicBinOp::MUL, 3, 4}};
            break;
        }
        case BasicTokenType::DIV: {
            op = std::optional<std::tuple<BasicBinOp, int, int>> {{BasicBinOp::DIV, 3, 4}};
            break;
        }
        default: {
            return std::nullopt;
        }
    }

    if(lprec < std::get<1>(op.value())) {
        ts.pop_front();
        return op;
    } else {
        return std::nullopt;
    }
}

static inline void basic_string_to_int_list(BasicExpressionList& list, const std::string& insert) {
    for(auto& c: insert) {
        auto inner = std::make_unique<BasicIntExpression>(c);
        list.push_back(std::move(inner));
    }
}

static bool basic_parse_var_list(const BasicParser& parser, std::list<char>& list, BasicConsole& console, BasicTokenList& ts) {
    // error if empty
    if(ts.empty()) {
        console.printLine("Error parsing var list");
        return false;
    }

    // parse character
    if(ts.front().typ == BasicTokenType::IDENTIFIER) {
        list.push_back(ts.front().sval.at(0));
        ts.pop_front();
    } else {
        // wrong type
        console.printLine("Error parsing var list: wrong token type");
        return false;
    }

    // if next is comma continue else return
    if(ts.empty() || ts.front().typ != BasicTokenType::COMMA)
        return true;

    // else eat comma and recurse
    ts.pop_front();
    return basic_parse_var_list(parser, list, console, ts);
}

std::list<char> BasicParser::parseVarList(BasicConsole& console, BasicTokenList& ts) const {
    std::list<char> var_list;
    bool res = basic_parse_var_list(*this, var_list, console, ts);

    if(res)
        return var_list;

    // else error: empty the list
    var_list.clear();
    return var_list;
}

static bool basic_parse_expression_list(const BasicParser& parser,
                                        BasicExpressionList& list,
                                        BasicConsole& console,
                                        BasicTokenList& ts) {
    // error if empty
    if(ts.empty()) {
        console.printLine("Error parsing expression list");
        return false;
    }

    // parse expression
    // first check if string
    if(ts.front().typ == BasicTokenType::STRING_LITERAL) {
        // convert and insert string as expression list
        basic_string_to_int_list(list, ts.front().sval);
        ts.pop_front();
    } else {
        // else parse expression
        if(auto expr = parser.parseExpression(console, ts)) {
            list.push_back(std::move(expr));
        } else {
            // rethrow error
            return false;
        }
    }

    // now if next token is comma, continue else return
    if(ts.empty() || ts.front().typ != BasicTokenType::COMMA)
        return true;

    // else comma, so eat the token and recurse
    ts.pop_front();
    return basic_parse_expression_list(parser, list, console, ts);
}

BasicExpressionList BasicParser::parseExpressionList(BasicConsole& console, BasicTokenList& ts) const {
    BasicExpressionList list;
    bool res = basic_parse_expression_list(*this, list, console, ts);

    if(res)
        return list;

    // else error: empty list is error
    list.clear();
    return list;
}

std::unique_ptr<BasicExpression> BasicParser::parseSimpleExpression(BasicConsole& console, BasicTokenList& ts) const {
    // error if empty
    if(ts.empty()) {
        console.printLine("Error unexpected EOF in expression");
        return nullptr;
    }

    // capture minus and eat possible plus
    bool isMinus = false;

    switch(ts.front().typ) {
        case BasicTokenType::MINUS: {
            isMinus = true;
            // no break, let fall
        }
        case BasicTokenType::PLUS: {
            ts.pop_front();
            break;
        }
        default:
            break;
    }

    // if now ts is empty, throw error
    if(ts.empty()) {
        console.printLine("Error unexpected EOF after unary `-` or `+`");
        return nullptr;
    }

    // parse simple expression
    std::unique_ptr<BasicExpression> expr;
    switch(ts.front().typ) {
        case BasicTokenType::IDENTIFIER: {
            expr = std::make_unique<BasicVarExpression>(ts.front().sval.at(0));
            ts.pop_front();
            break;
        }
        case BasicTokenType::INT_LITERAL: {
            expr = std::make_unique<BasicIntExpression>(ts.front().ival);
            ts.pop_front();
            break;
        }
        case BasicTokenType::LPAREN: {
            ts.pop_front();
            expr = this->parseExpression(console, ts);

            if(ts.empty()) {
                console.printLine("Error unexpected EOF, expected `)`");
                return nullptr;
            }

            if(ts.front().typ != BasicTokenType::RPAREN) {
                console.printLine("Error expected `)`");
                return nullptr;
            }

            // eat right paren
            ts.pop_front();
            break;
        }
        default: {
            console.printLine("Error expected expression.");
            return nullptr;
        }
    }

    // now if is minus, apply
    if(isMinus) {
        auto e     = std::make_unique<BasicUnaryExpression>(std::move(expr));
        e->isMinus = true;
        return e;
    }

    // else return expr
    return expr;
}

static std::unique_ptr<BasicExpression> basic_parse_precedence(const BasicParser& parser,
                                                               BasicConsole& console,
                                                               BasicTokenList& ts,
                                                               std::unique_ptr<BasicExpression> lhs,
                                                               int lprec) {
    auto op = parser.parseOp(console, ts, lprec);

    // if not op return lhs
    if(op == std::nullopt)
        return lhs;

    // now parse precedence right
    if(auto right = parser.parseSimpleExpression(console, ts)) {
        if(auto rhs = basic_parse_precedence(parser, console, ts, std::move(right), std::get<2>(op.value()))) {
            auto expr = std::make_unique<BasicBinaryExpression>(std::move(lhs), std::move(rhs), std::get<0>(op.value()));
            return basic_parse_precedence(parser, console, ts, std::move(expr), lprec);
        }
    }
    return nullptr;
}

std::unique_ptr<BasicExpression> BasicParser::parseBinExpression(BasicConsole& console, BasicTokenList& ts) const {
    if(auto left = this->parseSimpleExpression(console, ts)) {
        return basic_parse_precedence(*this, console, ts, std::move(left), 0);
    } else {
        return nullptr;
    }
}

std::unique_ptr<BasicExpression> BasicParser::parseExpression(BasicConsole& console, BasicTokenList& ts) const {
    return this->parseBinExpression(console, ts);
}

static std::optional<BasicRelOperation> basic_parse_relop(BasicConsole& console, BasicTokenList& ts) {
    if(ts.size() <= 1) {
        console.printLine("Error unexpected EOF expected comparation operator");
        return std::nullopt;
    }

    switch(ts.front().typ) {
        case BasicTokenType::ASSIGN: {
            ts.pop_front();
            return BasicRelOperation::EQUALS;
        }
        case BasicTokenType::LOWER: {
            ts.pop_front();

            switch(ts.front().typ) {
                case BasicTokenType::ASSIGN: {
                    ts.pop_front();
                    return BasicRelOperation::LOWER_EQUALS;
                }
                case BasicTokenType::GREATER: {
                    ts.pop_front();
                    return BasicRelOperation::NOT_EQUALS;
                }
                default:
                    return BasicRelOperation::LOWER;
            }
        }
        case BasicTokenType::GREATER: {
            ts.pop_front();

            if(ts.front().typ == BasicTokenType::ASSIGN) {
                ts.pop_front();
                return BasicRelOperation::GREATER_EQUALS;
            }

            return BasicRelOperation::GREATER;
        }
        default: {
            console.printLine("Expected comparation operator");
            return std::nullopt;
        }
    }
}

std::unique_ptr<BasicStatement> BasicParser::parseStatement(BasicConsole& console, BasicTokenList& ts) const {
    // parse the statement
    if(ts.empty()) {
        console.printLine("Unexpected EOF.");
        return nullptr;
    }

    switch(ts.front().typ) {
        case BasicTokenType::RETURN: {
            ts.pop_front();
            return std::make_unique<BasicReturnStatement>();
        }
        case BasicTokenType::RUN: {
            ts.pop_front();
            return std::make_unique<BasicRunStatement>();
        }
        case BasicTokenType::GOSUB: {
            ts.pop_front();
            auto e = this->parseExpression(console, ts);
            if(!e)
                return nullptr;
            return std::make_unique<BasicGoSubStatement>(std::move(e));
        }
        case BasicTokenType::PRINT: {
            ts.pop_front();
            auto el = this->parseExpressionList(console, ts);
            if(el.empty())
                return nullptr;
            return std::make_unique<BasicPrintStatement>(std::move(el));
        }
        case BasicTokenType::IF: {
            ts.pop_front();
            auto lcond = this->parseExpression(console, ts);
            if(!lcond)
                return nullptr;
            // parse relop
            auto relop = basic_parse_relop(console, ts);
            BasicRelOperation op;
            if(relop == std::nullopt)
                return nullptr;
            op         = relop.value();
            auto rcond = this->parseExpression(console, ts);
            if(!rcond)
                return nullptr;

            // consume THEN
            if(ts.empty() || ts.front().typ != BasicTokenType::THEN) {
                console.printLine("Expected THEN");
                return nullptr;
            }

            ts.pop_front();

            // parse then branch
            auto stmt = this->parseStatement(console, ts);
            if(!stmt)
                return nullptr;

            return std::make_unique<BasicIfStatement>(std::move(lcond), op, std::move(rcond), std::move(stmt));
        }
        case BasicTokenType::INPUT: {
            ts.pop_front();

            auto vs = this->parseVarList(console, ts);

            if(vs.empty())
                return nullptr;

            return std::make_unique<BasicInputStatement>(vs);
        }
        case BasicTokenType::LET: {
            ts.pop_front();

            if(ts.empty() || ts.front().typ != BasicTokenType::IDENTIFIER) {
                console.printLine("Expected identifier");
                return nullptr;
            }

            char c = ts.front().sval.at(0);
            ts.pop_front();

            // eat a =
            if(ts.empty() || ts.front().typ != BasicTokenType::ASSIGN) {
                console.printLine("Expected `=`");
                return nullptr;
            }
            ts.pop_front();

            // parse expression
            auto expr = this->parseExpression(console, ts);
            if(!expr)
                return nullptr;

            return std::make_unique<BasicLetStatement>(c, std::move(expr));
        }
        case BasicTokenType::GOTO: {
            ts.pop_front();

            auto expr = this->parseExpression(console, ts);

            if(!expr)
                return nullptr;

            return std::make_unique<BasicGotoStatement>(std::move(expr));
        }
        case BasicTokenType::END: {
            ts.pop_front();
            return std::make_unique<BasicEndStatement>();
        }
        default: {
            console.printLine("Error unknown statment");
            return nullptr;
        }
    }
}