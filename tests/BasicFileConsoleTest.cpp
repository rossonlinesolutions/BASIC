#include <BasicFileConsole.hpp>
#include <gtest/gtest.h>

TEST(AllTests, BasicFileConsoleReadTest) {
    BasicFileConsole console;

    std::string content = R"X(10 REM a test here
20 REM GOTO 10
30 LET X = 9
40 RUN)X";
    console.setContent(content);

    std::string t1 = "10 REM a test here";
    std::string t2 = "20 REM GOTO 10";
    std::string t3 = "30 LET X = 9";
    std::string t4 = "40 RUN";

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t1, *r);
        delete r;
    }

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t2, *r);
        delete r;
    }

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t3, *r);
        delete r;
    }

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t4, *r);
        delete r;
    }

    ASSERT_EQ(console.nextLine(), nullptr);
    ASSERT_EQ(console.nextLine(), nullptr);
}

TEST(AllTests, BasicFileConsoleWindowsTest) {
    BasicFileConsole console;

    std::string content = "10 INPUT C\r\n20 RUN";

    console.setContent(content);

    std::string t1 = "10 INPUT C";
    std::string t2 = "20 RUN";

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t1, *r);
        delete r;
    }

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t2, *r);
        delete r;
    }

    ASSERT_EQ(console.nextLine(), nullptr);
}

TEST(AllTests, BasicFileConsoleLinuxTest) {
    BasicFileConsole console;

    std::string content = "10 INPUT C\n20 RUN";

    console.setContent(content);

    std::string t1 = "10 INPUT C";
    std::string t2 = "20 RUN";

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t1, *r);
        delete r;
    }

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t2, *r);
        delete r;
    }

    ASSERT_EQ(console.nextLine(), nullptr);
}

TEST(AllTests, BasicFileConsoleMacOSTest) {
    BasicFileConsole console;

    std::string content = "10 INPUT C\r20 RUN";

    console.setContent(content);

    std::string t1 = "10 INPUT C";
    std::string t2 = "20 RUN";

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t1, *r);
        delete r;
    }

    {
        std::string* r = console.nextLine();
        ASSERT_EQ(t2, *r);
        delete r;
    }

    ASSERT_EQ(console.nextLine(), nullptr);
}
