#pragma once

#include <BasicExpression.hpp>
#include <BasicStatement.hpp>
#include <memory>

class BasicLetStatement : public BasicStatement {
    protected:
    std::string property_string() const override;

    public:
    char variable;
    std::unique_ptr<BasicExpression> expr;

    BasicLetStatement(char variable, std::unique_ptr<BasicExpression> expr) :
        BasicStatement {"LetStatement"}, variable(variable), expr(std::move(expr)) {
    }

    int execute(BasicConsole& console, BasicEnv& env) const override;
};
