#pragma once

#include <BasicExpression.hpp>
#include <BasicStatement.hpp>
#include <memory>

class BasicLetStatement : public BasicStatement {
    protected:
    std::string property_string() const override;

    public:
    BasicExpression::Variable variable;
    std::unique_ptr<BasicExpression> expr;

    BasicLetStatement(BasicExpression::Variable variable, std::unique_ptr<BasicExpression> expr) :
        BasicStatement {"LetStatement"}, variable(std::move(variable)), expr(std::move(expr)) {
    }

    int execute(BasicConsole& console, BasicEnv& env) const override;
};
