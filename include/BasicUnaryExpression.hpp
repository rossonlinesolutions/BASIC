#pragma once

#include <BasicExpression.hpp>
#include <memory>

class BasicUnaryExpression : public BasicExpression {
    protected:
    std::string property_string() override;

    public:
    bool isMinus = false;
    std::unique_ptr<BasicExpression> expr;

    BasicUnaryExpression(std::unique_ptr<BasicExpression> expr) : BasicExpression {"UnaryExpression"}, expr(std::move(expr)) {
    }

    int eval(BasicEnv& env) const override;
};
