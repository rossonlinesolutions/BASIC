#include "BasicTestConsole.hpp"

#include <BasicConsole.hpp>
#include <BasicEnv.hpp>
#include <BasicInputStatement.hpp>
#include <gtest/gtest.h>

TEST(AllTests, BasicInputStatementOne) {
    BasicInputStatement stmt {{'A'}};
    BasicEnv env;
    BasicTestConsole console;
    console.in = "a";

    // run
    int res = stmt.execute(console, env);
    int a   = env.get('A');

    // assert
    ASSERT_EQ(res, 0);
    ASSERT_EQ(a, 'a');
}

TEST(AllTests, BasicInputStatementThree) {
    BasicInputStatement stmt {{'A', 'B', 'Q'}};
    BasicEnv env;
    BasicTestConsole console;
    console.in = "abq";

    // run
    int res = stmt.execute(console, env);
    int a   = env.get('A');
    int b   = env.get('B');
    int q   = env.get('Q');

    // assert
    ASSERT_EQ(res, 0);
    ASSERT_EQ(a, 'a');
    ASSERT_EQ(b, 'b');
    ASSERT_EQ(q, 'q');
}

TEST(AllTests, BasicInputStatementEOF) {
    BasicInputStatement stmt {{'A', 'B', 'Q'}};
    BasicEnv env;
    BasicTestConsole console;
    console.in = "ad";

    // run
    int res = stmt.execute(console, env);

    // assert
    ASSERT_EQ(res, -1);
}

TEST(AllTests, BasicInputStatementMultiline) {
    BasicInputStatement stmt {{'A', 'B', 'Q'}};
    BasicEnv env;
    BasicTestConsole console;
    console.in = "ab\nq";

    // run
    int res = stmt.execute(console, env);
    int a   = env.get('A');
    int b   = env.get('B');
    int q   = env.get('Q');

    // assert
    ASSERT_EQ(res, 0);
    ASSERT_EQ(a, 'a');
    ASSERT_EQ(b, 'b');
    ASSERT_EQ(q, 'q');
}

TEST(AllTests, BasicInputStatementMultiEmptyLine) {
    BasicInputStatement stmt {{'A', 'B', 'Q'}};
    BasicEnv env;
    BasicTestConsole console;
    console.in = "a\nb\n\nq\n";

    // run
    int res = stmt.execute(console, env);
    int a   = env.get('A');
    int b   = env.get('B');
    int q   = env.get('Q');

    // assert
    ASSERT_EQ(res, 0);
    ASSERT_EQ(a, 'a');
    ASSERT_EQ(b, 'b');
    ASSERT_EQ(q, 'q');
}

TEST(AllTests, BasicInputStatementMultilineEOF) {
    BasicInputStatement stmt {{'A', 'B', 'Q'}};
    BasicEnv env;
    BasicTestConsole console;
    console.in = "ad\n\n\n\n";

    // run
    int res = stmt.execute(console, env);

    // assert
    ASSERT_EQ(res, -1);
}

TEST(AllTests, BasicInputStatementTooLong) {
    BasicInputStatement stmt {{'A', 'B', 'Q'}};
    BasicEnv env;
    BasicTestConsole console;
    console.in = "abqzz";

    // run
    int res = stmt.execute(console, env);
    int a   = env.get('A');
    int b   = env.get('B');
    int q   = env.get('Q');

    // assert
    ASSERT_EQ(res, 0);
    ASSERT_EQ(a, 'a');
    ASSERT_EQ(b, 'b');
    ASSERT_EQ(q, 'q');
}

TEST(AllTests, BasicInputStatementBuffered) {
    BasicInputStatement stmt {{'A', 'B', 'Q'}};
    BasicInputStatement stmt2 {{'B', 'Z'}};
    BasicEnv env;
    BasicTestConsole console;
    console.in = "abqbz";

    // run
    int res = stmt.execute(console, env);
    int a   = env.get('A');
    int b   = env.get('B');
    int q   = env.get('Q');

    // run second
    int res2 = stmt2.execute(console, env);
    int b2   = env.get('B');
    int z2   = env.get('Z');

    // assert
    ASSERT_EQ(res, 0);
    ASSERT_EQ(a, 'a');
    ASSERT_EQ(b, 'b');
    ASSERT_EQ(q, 'q');

    // assert second
    ASSERT_EQ(res2, 0);
    ASSERT_EQ(b2, 'b');
    ASSERT_EQ(z2, 'z');
}

TEST(AllTests, BasicInputStatementOverride) {
    BasicInputStatement stmt {{'A', 'B', 'B'}};
    BasicEnv env;
    BasicTestConsole console;
    console.in = "aqbz";

    // run
    int res = stmt.execute(console, env);
    int a   = env.get('A');
    int b   = env.get('B');

    // assert
    ASSERT_EQ(res, 0);
    ASSERT_EQ(a, 'a');
    ASSERT_EQ(b, 'b');
}
