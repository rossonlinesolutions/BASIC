#include <BasicGoSubStatement.hpp>
#include <BasicIntExpression.hpp>
#include <BasicTerminal.hpp>
#include <gtest/gtest.h>

TEST(AllTests, BasicGoSubStatementOne) {
    BasicEnv env;
    env.set_line(10);
    BasicTerminal console;
    auto inner = std::make_unique<BasicIntExpression>(1);
    BasicGoSubStatement stmt {std::move(inner)};

    int res = stmt.execute(console, env);

    int r1 = env.popReturnAddress();
    int r2 = env.popReturnAddress();

    ASSERT_EQ(res, 1);
    ASSERT_EQ(r1, 10);
    ASSERT_EQ(r2, -1);
}

TEST(AllTests, BasicGoSubStatementNegative) {
    BasicEnv env;
    env.set_line(10);
    BasicTerminal console;
    auto inner = std::make_unique<BasicIntExpression>(-42);
    BasicGoSubStatement stmt {std::move(inner)};

    int res = stmt.execute(console, env);

    ASSERT_EQ(res, -1);
}
