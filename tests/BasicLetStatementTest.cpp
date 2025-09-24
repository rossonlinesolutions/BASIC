#include <BasicIntExpression.hpp>
#include <BasicLetStatement.hpp>
#include <BasicTerminal.hpp>
#include <gtest/gtest.h>

TEST(AllTests, BasicLetStatementZero) {
    BasicEnv env;
    env.set('Q', 99);
    BasicTerminal console;
    auto inner = std::make_unique<BasicIntExpression>(0);
    BasicLetStatement stmt {'Q', std::move(inner)};

    int res = stmt.execute(console, env);
    int q   = env.get('Q');

    ASSERT_EQ(res, 0);
    ASSERT_EQ(q, 0);
}

TEST(AllTests, BasicLetStatementFortyTwo) {
    BasicEnv env;
    env.set('Q', 99);
    BasicTerminal console;
    auto inner = std::make_unique<BasicIntExpression>(42);
    BasicLetStatement stmt {'Q', std::move(inner)};

    int res = stmt.execute(console, env);
    int q   = env.get('Q');

    ASSERT_EQ(res, 0);
    ASSERT_EQ(q, 42);
}
