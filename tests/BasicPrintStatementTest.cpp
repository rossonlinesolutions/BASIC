#include "BasicTestConsole.hpp"

#include <BasicPrintStatement.hpp>
#include <BasicVarExpression.hpp>
#include <gtest/gtest.h>

TEST(AllTests, BasicPrintStatementHello) {
    BasicEnv env;

    for(int i = 0; i < 26; i++) {
        char c = 'A' + i;
        env.set(c, c);
    }

    BasicTestConsole console;

    auto h1 = std::make_unique<BasicVarExpression>('H');
    auto e1 = std::make_unique<BasicVarExpression>('E');
    auto l1 = std::make_unique<BasicVarExpression>('L');
    auto l2 = std::make_unique<BasicVarExpression>('L');
    auto o1 = std::make_unique<BasicVarExpression>('O');

    BasicExpressionList expr_list;

    expr_list.push_back(std::move(h1));
    expr_list.push_back(std::move(e1));
    expr_list.push_back(std::move(l1));
    expr_list.push_back(std::move(l2));
    expr_list.push_back(std::move(o1));

    BasicPrintStatement stmt {std::move(expr_list)};

    int res         = stmt.execute(console, env);
    std::string out = console.out;

    ASSERT_EQ(res, 0);
    ASSERT_EQ(out, "HELLO\n");
}