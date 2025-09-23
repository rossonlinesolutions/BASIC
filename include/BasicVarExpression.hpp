#pragma once

#include <BasicExpression.hpp>

class BasicVarExpression : public BasicExpression {
    protected:
    std::string property_string() override;

    public:
    char value;

    BasicVarExpression(char value) : BasicExpression {"VarExpression"}, value(value) {
    }
    int eval(BasicEnv& env) const override;
};