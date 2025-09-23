#include <BasicIntExpression.hpp>
#include <BasicUnaryExpression.hpp>
#include <BasicVarExpression.hpp>
#include <gtest/gtest.h>
#include <memory>

TEST(AllTests, BasicUnaryExpressionSimple) {
    BasicEnv env;
    auto inner = std::make_unique<BasicIntExpression>(42);
    BasicUnaryExpression expr {std::move(inner)};

    // eval
    int res = expr.eval(env);

    // assert
    ASSERT_EQ(res, 42);
}

TEST(AllTests, BasicUnaryExpressionSimpleMinus) {
    BasicEnv env;
    auto inner = std::make_unique<BasicIntExpression>(42);
    BasicUnaryExpression expr {std::move(inner)};
    expr.isMinus = true;

    // eval
    int res = expr.eval(env);

    // assert
    ASSERT_EQ(res, -42);
}

TEST(AllTests, BasicUnaryExpressionZero) {
    BasicEnv env;
    auto inner = std::make_unique<BasicIntExpression>(0);
    BasicUnaryExpression expr {std::move(inner)};

    // eval
    int res = expr.eval(env);

    // assert
    ASSERT_EQ(res, 0);
}

TEST(AllTests, BasicUnaryExpressionMinusZero) {
    BasicEnv env;
    auto inner = std::make_unique<BasicIntExpression>(0);
    BasicUnaryExpression expr {std::move(inner)};
    expr.isMinus = true;

    // eval
    int res = expr.eval(env);

    // assert
    ASSERT_EQ(res, 0);
}

TEST(AllTests, BasicUnaryExpressionSimpleVar) {
    BasicEnv env;
    env.set('Q', 42);
    auto inner = std::make_unique<BasicVarExpression>('Q');
    BasicUnaryExpression expr {std::move(inner)};

    // eval
    int res = expr.eval(env);

    // assert
    ASSERT_EQ(res, 42);
}

TEST(AllTests, BasicUnaryExpressionNegativeVar) {
    BasicEnv env;
    env.set('Q', -142);
    auto inner = std::make_unique<BasicVarExpression>('Q');
    BasicUnaryExpression expr {std::move(inner)};

    // eval
    int res = expr.eval(env);

    // assert
    ASSERT_EQ(res, -142);
}

TEST(AllTests, BasicUnaryExpressionMinusVar) {
    BasicEnv env;
    env.set('Q', 42);
    auto inner = std::make_unique<BasicVarExpression>('Q');
    BasicUnaryExpression expr {std::move(inner)};
    expr.isMinus = true;

    // eval
    int res = expr.eval(env);

    // assert
    ASSERT_EQ(res, -42);
}

TEST(AllTests, BasicUnaryExpressionMinusNegativeVar) {
    BasicEnv env;
    env.set('Q', -142);
    auto inner = std::make_unique<BasicVarExpression>('Q');
    BasicUnaryExpression expr {std::move(inner)};
    expr.isMinus = true;

    // eval
    int res = expr.eval(env);

    // assert
    ASSERT_EQ(res, 142);
}
