#pragma once

#include <BasicExpression.hpp>
#include <BasicStatement.hpp>
#include <list>
#include <memory>

class BasicPrintStatement : public BasicStatement {
    protected:
    std::string property_string() const override;

    public:
    BasicExpressionList expr_list;

    BasicPrintStatement(BasicExpressionList expr_list) : BasicStatement {"PrintStatement"}, expr_list(std::move(expr_list)) {
    }

    int execute(BasicConsole& console, BasicEnv& env) const override;
};
