#include <BasicGotoStatement.hpp>
#include <BasicIntExpression.hpp>
#include <BasicTerminal.hpp>
#include <gtest/gtest.h>

TEST(AllTests, BasicGotoStatementZero) {
    BasicEnv env;
    BasicTerminal console;
    auto inner = std::make_unique<BasicIntExpression>(0);
    BasicGotoStatement stmt {std::move(inner)};

    int res      = stmt.execute(console, env);
    int ret_addr = env.popReturnAddress();

    ASSERT_EQ(res, 0);
    ASSERT_EQ(ret_addr, -1);
}

TEST(AllTests, BasicGotoStatementFortyTwo) {
    BasicEnv env;
    BasicTerminal console;
    auto inner = std::make_unique<BasicIntExpression>(42);
    BasicGotoStatement stmt {std::move(inner)};

    int res      = stmt.execute(console, env);
    int ret_addr = env.popReturnAddress();

    ASSERT_EQ(res, 42);
    ASSERT_EQ(ret_addr, -1);
}

TEST(AllTests, BasicGotoStatementNegative) {
    BasicEnv env;
    BasicTerminal console;
    auto inner = std::make_unique<BasicIntExpression>(-733);
    BasicGotoStatement stmt {std::move(inner)};

    int res      = stmt.execute(console, env);
    int ret_addr = env.popReturnAddress();

    ASSERT_EQ(res, -1);
    ASSERT_EQ(ret_addr, -1);
}
