#include <BasicLexer.hpp>
#include <BasicTerminal.hpp>
#include <gtest/gtest.h>

TEST(AllTests, LexerRun) {
    std::string input = "RUN";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 1);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::RUN);
}

TEST(AllTests, LexerIdentifier) {
    std::string input = "Q";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 1);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::IDENTIFIER);
    ASSERT_EQ(lexer.tokens.front().sval, "Q");
}

TEST(AllTests, LexerIdentifierMultiChar) {
    std::string input = "AQ";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.hasError(), true);
}

TEST(AllTests, LexerIdentifierSpaced) {
    std::string input = "A Q";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 2);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::IDENTIFIER);
    ASSERT_EQ(lexer.tokens.front().sval, "A");
    ASSERT_EQ(lexer.tokens.back().typ, BasicTokenType::IDENTIFIER);
    ASSERT_EQ(lexer.tokens.back().sval, "Q");
}

TEST(AllTests, LexerKeywordIdent) {
    std::string input = "LET X";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 2);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::LET);
    ASSERT_EQ(lexer.tokens.back().typ, BasicTokenType::IDENTIFIER);
    ASSERT_EQ(lexer.tokens.back().sval, "X");
}

TEST(AllTests, LexerLowercase) {
    std::string input = "x";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.hasError(), true);
}

TEST(AllTests, LexerNumberZero) {
    std::string input = "0";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 1);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::INT_LITERAL);
    ASSERT_EQ(lexer.tokens.front().ival, 0);
}

TEST(AllTests, LexerNumberFortyTwo) {
    std::string input = "42";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 1);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::INT_LITERAL);
    ASSERT_EQ(lexer.tokens.front().ival, 42);
}

TEST(AllTests, LexerNumberAsciiAt) {
    std::string input = "#@";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 1);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::INT_LITERAL);
    ASSERT_EQ(lexer.tokens.front().ival, '@');
}

TEST(AllTests, LexerNumberAsciiA) {
    std::string input = "#a";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 1);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::INT_LITERAL);
    ASSERT_EQ(lexer.tokens.front().ival, 'a');
}

TEST(AllTests, LexerNumberComplex) {
    std::string input = "1234567890";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 1);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::INT_LITERAL);
    ASSERT_EQ(lexer.tokens.front().ival, 1234567890);
}

TEST(AllTests, LexerStringEmpty) {
    std::string input = "\"\"";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 1);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::STRING_LITERAL);
    ASSERT_EQ(lexer.tokens.front().sval, "");
}

TEST(AllTests, LexerStringHello) {
    std::string input = "\"hello, world\"";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.tokens.size(), 1);
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::STRING_LITERAL);
    ASSERT_EQ(lexer.tokens.front().sval, "hello, world");
}

TEST(AllTests, LexerStringUnTerm) {
    std::string input = "\"hell this is unterminated";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.hasError(), true);
}

TEST(AllTests, LexerEmpty) {
    std::string input = "";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.size(), 0);
}

TEST(AllTests, LexerIfStatement) {
    std::string input = "10 IF A = B THEN PRINT \"OK\"";
    BasicTerminal terminal;
    BasicLexer lexer {terminal, input};

    // run
    lexer.run();

    // assert
    ASSERT_EQ(lexer.hasError(), false);
    ASSERT_EQ(lexer.tokens.size(), 8);

    // 10
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::INT_LITERAL);
    ASSERT_EQ(lexer.tokens.front().ival, 10);

    lexer.tokens.pop_front();

    // IF
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::IF);

    lexer.tokens.pop_front();

    // A
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::IDENTIFIER);
    ASSERT_EQ(lexer.tokens.front().sval, "A");

    lexer.tokens.pop_front();

    // =
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::ASSIGN);

    lexer.tokens.pop_front();

    // B
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::IDENTIFIER);
    ASSERT_EQ(lexer.tokens.front().sval, "B");

    lexer.tokens.pop_front();

    // THEN
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::THEN);

    lexer.tokens.pop_front();

    // PRINT
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::PRINT);

    lexer.tokens.pop_front();

    // "OK"
    ASSERT_EQ(lexer.tokens.front().typ, BasicTokenType::STRING_LITERAL);
    ASSERT_EQ(lexer.tokens.front().sval, "OK");
}