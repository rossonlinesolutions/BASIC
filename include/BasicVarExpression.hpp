#pragma once

#include <BasicExpression.hpp>

class BasicVarExpression : public BasicExpression {
    protected:
    std::string property_string() override;

    public:
    BasicExpression::Variable value;

    BasicVarExpression(BasicExpression::Variable value) : BasicExpression {"VarExpression"}, value(std::move(value)) {
    }
    int eval(BasicEnv& env) const override;
};
