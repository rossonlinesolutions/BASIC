#pragma once

#include <BasicExpression.hpp>
#include <BasicStatement.hpp>
#include <memory>

class BasicGoSubStatement : public BasicStatement {
    protected:
    std::string property_string() const override;

    public:
    std::unique_ptr<BasicExpression> expr;

    BasicGoSubStatement(std::unique_ptr<BasicExpression> expr) : BasicStatement {"GoSubStatement"}, expr(std::move(expr)) {
    }

    int execute(BasicConsole& console, BasicEnv& env) const override;
};
