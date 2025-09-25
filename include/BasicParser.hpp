#pragma once

#include <BasicBinaryExpression.hpp>
#include <BasicConsole.hpp>
#include <BasicStatement.hpp>
#include <BasicToken.hpp>
#include <list>
#include <memory>
#include <optional>
#include <tuple>

using BasicTokenList = std::list<BasicToken>;
using BasicOperation = std::optional<std::tuple<BasicBinOp, int, int>>;

class BasicParser {
    public:
    BasicParser() {
    }

    std::unique_ptr<BasicStatement> parseLine(BasicConsole& console, BasicTokenList& ts) const;
    std::unique_ptr<BasicExpression> parseExpression(BasicConsole& console, BasicTokenList& ts) const;
    std::unique_ptr<BasicStatement> parseStatement(BasicConsole& console, BasicTokenList& ts) const;
    std::list<char> parseVarList(BasicConsole& console, BasicTokenList& ts) const;
    std::unique_ptr<BasicExpression> parseBinExpression(BasicConsole& console, BasicTokenList& ts) const;
    std::unique_ptr<BasicExpression> parseSimpleExpression(BasicConsole& console, BasicTokenList& ts) const;
    BasicExpressionList parseExpressionList(BasicConsole& console, BasicTokenList& ts) const;
    BasicOperation parseOp(BasicConsole& console, BasicTokenList& ts, int lprec) const;
};
