#include <BasicIfStatement.hpp>
#include <BasicIntExpression.hpp>
#include <BasicLetStatement.hpp>
#include <BasicTerminal.hpp>
#include <gtest/gtest.h>

TEST(AllTests, BasicIfStatementTrue) {
    BasicEnv env;
    env.set('R', 1);
    BasicTerminal console;
    auto left  = std::make_unique<BasicIntExpression>(1);
    auto right = std::make_unique<BasicIntExpression>(1);
    auto e     = std::make_unique<BasicIntExpression>(42);
    auto then  = std::make_unique<BasicLetStatement>('R', std::move(e));
    BasicIfStatement stmt {std::move(left), BasicRelOperation::EQUALS, std::move(right), std::move(then)};

    int res = stmt.execute(console, env);
    int r   = env.get('R');

    ASSERT_EQ(res, 0);
    ASSERT_EQ(r, 42);
}

TEST(AllTests, BasicIfStatementFalse) {
    BasicEnv env;
    env.set('R', 1);
    BasicTerminal console;
    auto left  = std::make_unique<BasicIntExpression>(1);
    auto right = std::make_unique<BasicIntExpression>(1);
    auto e     = std::make_unique<BasicIntExpression>(42);
    auto then  = std::make_unique<BasicLetStatement>('R', std::move(e));
    BasicIfStatement stmt {std::move(left), BasicRelOperation::NOT_EQUALS, std::move(right), std::move(then)};

    int res = stmt.execute(console, env);
    int r   = env.get('R');

    ASSERT_EQ(res, 0);
    ASSERT_EQ(r, 1);
}
