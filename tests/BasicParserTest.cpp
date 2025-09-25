#include "BasicTestConsole.hpp"

#include <BasicLexer.hpp>
#include <BasicParser.hpp>
#include <BasicToken.hpp>
#include <gtest/gtest.h>

static BasicTokenList parser_test_setup(BasicConsole& console, const std::string& src) {
    BasicLexer lexer {console, src};
    lexer.run();
    return lexer.tokens;
}

TEST(AllTests, ParserRun) {
    std::string input = "RUN";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);
    ASSERT_EQ(stmt->to_string(), "RunStatement{}");
}

TEST(AllTests, ParserRunJunk) {
    std::string input = "RUN 10";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_EQ(stmt, nullptr);
}

TEST(AllTests, ParserReturn) {
    std::string input = "RETURN";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);
    ASSERT_EQ(stmt->to_string(), "ReturnStatement{}");
}

TEST(AllTests, ParserReturnJunk) {
    std::string input = "RETURN 10";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_EQ(stmt, nullptr);
}

TEST(AllTests, ParserGoSubMissing) {
    std::string input = "GOSUB";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_EQ(stmt, nullptr);
}

TEST(AllTests, ParserGoSubInt) {
    std::string input = "GOSUB 10";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);
    ASSERT_EQ(stmt->to_string(), "GoSubStatement{IntExpression{10}}");
}

TEST(AllTests, ParserGoSubVar) {
    std::string input = "GOSUB F";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);
    ASSERT_EQ(stmt->to_string(), "GoSubStatement{VarExpression{F}}");
}
