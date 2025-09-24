#pragma once

#include <BasicExpression.hpp>
#include <BasicStatement.hpp>
#include <memory>

enum class BasicRelOperation {
    LOWER,
    GREATER,
    NOT_EQUALS,
    EQUALS,
    LOWER_EQUALS,
    GREATER_EQUALS
};

class BasicIfStatement : public BasicStatement {
    protected:
    std::string property_string() const override;

    public:
    std::unique_ptr<BasicExpression> lcondition;
    BasicRelOperation op;
    std::unique_ptr<BasicExpression> rcondition;
    std::unique_ptr<BasicStatement> stmt;

    BasicIfStatement(std::unique_ptr<BasicExpression> lcondition,
                     BasicRelOperation op,
                     std::unique_ptr<BasicExpression> rcondition,
                     std::unique_ptr<BasicStatement> stmt) :
        BasicStatement {"IfStatement"}, lcondition(std::move(lcondition)), op(op), rcondition(std::move(rcondition)),
        stmt(std::move(stmt)) {
    }

    int execute(BasicConsole& console, BasicEnv& env) const override;
};