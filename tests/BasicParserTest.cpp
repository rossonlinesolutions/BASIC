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

TEST(AllTests, ParserGoSubBinary) {
    std::string input = "GOSUB 3 * Q";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);
    ASSERT_EQ(stmt->to_string(), "GoSubStatement{BinaryExpression{IntExpression{3},VarExpression{Q},MUL}}");
}

TEST(AllTests, ParserGoSubBinaryPrec) {
    std::string input = "GOSUB 1 + 3 * Q";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);
    ASSERT_EQ(
        stmt->to_string(),
        "GoSubStatement{BinaryExpression{IntExpression{1},BinaryExpression{IntExpression{3},VarExpression{Q},MUL},PLUS}}");
}

TEST(AllTests, ParserGoSubBinaryPrec2) {
    std::string input = "GOSUB 1 + 3 * Q + 4";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);
    ASSERT_EQ(stmt->to_string(),
              "GoSubStatement{BinaryExpression{BinaryExpression{IntExpression{1},BinaryExpression{IntExpression{3},"
              "VarExpression{Q},MUL},PLUS},IntExpression{4},PLUS}}");
}

TEST(AllTests, ParserGoSubLong) {
    std::string input = "GOSUB 1 A";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_EQ(stmt, nullptr);
}

TEST(AllTests, ParserPrintInt) {
    std::string input = "PRINT 42";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);
    ASSERT_EQ(stmt->to_string(), "PrintStatement{IntExpression{42}}");
}

TEST(AllTests, ParserPrintStringHello) {
    std::string input = "PRINT \"HELLO\", 10";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);

    std::string expected = "PrintStatement{";
    std::string hello    = "HELLO\n";
    for(auto& c: hello) {
        expected += "IntExpression{";
        expected += std::to_string((int)c);
        expected += "},";
    }
    expected.pop_back();
    expected += "}";

    ASSERT_EQ(stmt->to_string(), expected);
}

TEST(AllTests, ParserPrintMixed) {
    std::string input = "PRINT \"AB\", A, B + 1, 10, 20 * 2";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_NE(stmt, nullptr);

    std::string expected = "PrintStatement{IntExpression{";
    expected += std::to_string((int)'A');
    expected += "},IntExpression{";
    expected += std::to_string((int)'B');
    expected += "},VarExpression{";
    expected.push_back('A');
    expected += "},BinaryExpression{VarExpression{";
    expected.push_back('B');
    expected += "},IntExpression{1},PLUS},IntExpression{10},BinaryExpression{IntExpression{20},IntExpression{2},MUL}}";

    ASSERT_EQ(stmt->to_string(), expected);
}

TEST(AllTests, ParserPrintDanglingComma) {
    std::string input = "PRINT \"AB\", A, B + 1, 10, 20 * 2,";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_EQ(stmt, nullptr);
}

TEST(AllTests, ParserPrintMissing) {
    std::string input = "PRINT";
    BasicTestConsole console;
    BasicParser parser;
    auto ts = parser_test_setup(console, input);

    auto stmt = parser.parseLine(console, ts);

    ASSERT_EQ(stmt, nullptr);
}