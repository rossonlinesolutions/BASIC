#include <BasicEnv.hpp>
#include <gtest/gtest.h>

TEST(AllTests, BasicEnvSimpleTest) {
    BasicEnv env;
    env.set('A', 3);
    env.set('Z', 9);
    env.set('Q', 42);
    env.set('Z', 6);

    int a = env.get('A');
    int z = env.get('Z');
    int q = env.get('Q');

    ASSERT_EQ(a, 3);
    ASSERT_EQ(z, 6);
    ASSERT_EQ(q, 42);
}

TEST(AllTests, BasicEnvCallStackTest) {
    BasicEnv env;
    env.set_line(10);
    env.pushCurrLine();

    int c1 = env.popReturnAddress();
    int c2 = env.popReturnAddress();

    ASSERT_EQ(c1, 10);
    ASSERT_EQ(c2, -1);
}
