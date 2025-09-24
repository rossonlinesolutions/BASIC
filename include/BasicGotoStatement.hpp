#pragma once

#include <BasicExpression.hpp>
#include <BasicStatement.hpp>
#include <memory>

class BasicGotoStatement : public BasicStatement {
    protected:
    std::string property_string() const override;

    public:
    std::unique_ptr<BasicExpression> expr;

    BasicGotoStatement(std::unique_ptr<BasicExpression> expr) : BasicStatement {"GotoStatement"}, expr(std::move(expr)) {
    }

    int execute(BasicConsole& console, BasicEnv& env) const override;
};
