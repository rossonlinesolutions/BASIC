#pragma once

#include <BasicExpression.hpp>

class BasicIntExpression : public BasicExpression {
    private:
    int value;

    protected:
    std::string property_string() override;

    public:
    BasicIntExpression(int value) : BasicExpression {"IntExpression"}, value(value) {
    }
    int eval(BasicEnv& env) const override;
};
