#pragma once

#include <BasicExpression.hpp>
#include <memory>

enum class BasicBinOp {
    PLUS,
    MINUS,
    MUL,
    DIV
};

class BasicBinaryExpression : public BasicExpression {
    protected:
    std::string property_string() override;

    public:
    std::unique_ptr<BasicExpression> lexpr;
    std::unique_ptr<BasicExpression> rexpr;
    BasicBinOp op;

    BasicBinaryExpression(std::unique_ptr<BasicExpression> lexpr, std::unique_ptr<BasicExpression> rexpr, BasicBinOp op) :
        BasicExpression {"BinaryExpression"}, lexpr(std::move(lexpr)), rexpr(std::move(rexpr)), op(op) {
    }

    int eval(BasicEnv& env) const override;
};