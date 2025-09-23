#include <BasicBinaryExpression.hpp>
#include <BasicIntExpression.hpp>
#include <gtest/gtest.h>
#include <memory>

TEST(AllTests, BasicBinaryExpressionOneMinusOne) {
    BasicEnv env;
    auto left  = std::make_unique<BasicIntExpression>(1);
    auto right = std::make_unique<BasicIntExpression>(1);
    BasicBinaryExpression expr {std::move(left), std::move(right), BasicBinOp::MINUS};

    int res = expr.eval(env);

    ASSERT_EQ(res, 0);
}

TEST(AllTests, BasicBinaryExpressionTenMinusFive) {
    BasicEnv env;
    auto left  = std::make_unique<BasicIntExpression>(10);
    auto right = std::make_unique<BasicIntExpression>(5);
    BasicBinaryExpression expr {std::move(left), std::move(right), BasicBinOp::MINUS};

    int res = expr.eval(env);

    ASSERT_EQ(res, 5);
}

TEST(AllTests, BasicBinaryExpressionThreeTimesFour) {
    BasicEnv env;
    auto left  = std::make_unique<BasicIntExpression>(3);
    auto right = std::make_unique<BasicIntExpression>(4);
    BasicBinaryExpression expr {std::move(left), std::move(right), BasicBinOp::MUL};

    int res = expr.eval(env);

    ASSERT_EQ(res, 12);
}

TEST(AllTests, BasicBinaryExpressionSevenTimesZero) {
    BasicEnv env;
    auto left  = std::make_unique<BasicIntExpression>(7);
    auto right = std::make_unique<BasicIntExpression>(0);
    BasicBinaryExpression expr {std::move(left), std::move(right), BasicBinOp::MUL};

    int res = expr.eval(env);

    ASSERT_EQ(res, 0);
}

TEST(AllTests, BasicBinaryExpressionEightDividedByTwo) {
    BasicEnv env;
    auto left  = std::make_unique<BasicIntExpression>(8);
    auto right = std::make_unique<BasicIntExpression>(2);
    BasicBinaryExpression expr {std::move(left), std::move(right), BasicBinOp::DIV};

    int res = expr.eval(env);

    ASSERT_EQ(res, 4);
}

TEST(AllTests, BasicBinaryExpressionNineDividedByThree) {
    BasicEnv env;
    auto left  = std::make_unique<BasicIntExpression>(9);
    auto right = std::make_unique<BasicIntExpression>(3);
    BasicBinaryExpression expr {std::move(left), std::move(right), BasicBinOp::DIV};

    int res = expr.eval(env);

    ASSERT_EQ(res, 3);
}