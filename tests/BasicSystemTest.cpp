#include "BasicTestConsole.hpp"

#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>

namespace basic {
    int run(int argc, char** argv, BasicConsole* console);
}

namespace fs = std::filesystem;

struct SystemTestCase {
    std::string name;
    fs::path dir;
};

class SystemTest : public ::testing::TestWithParam<SystemTestCase> {};

TEST_P(SystemTest, ExecutesCorrectly) {
    const auto& test          = GetParam();
    fs::path stdinPath        = test.dir / "stdin.txt";
    fs::path sourcePath       = test.dir / "source.bas";
    fs::path expectedOutPath  = test.dir / "expected_stdout.txt";
    fs::path expectedExitPath = test.dir / "expected_exit.txt";

    std::ifstream in(stdinPath), src(sourcePath), out(expectedOutPath), exit(expectedExitPath);
    ASSERT_TRUE(in && src && out && exit) << "Missing test files in " << test.name;

    std::stringstream stdinBuf, sourceBuf, expectedOutBuf;
    stdinBuf << in.rdbuf();
    sourceBuf << src.rdbuf();
    expectedOutBuf << out.rdbuf();

    int expectedExitCode;
    exit >> expectedExitCode;

    BasicTestConsole console;
    console.in  = stdinBuf.str();
    console.src = sourceBuf.str();

    int actualExitCode = basic::run(0, nullptr, &console);

    EXPECT_EQ(console.out, expectedOutBuf.str()) << "Output mismatch in " << test.name;
    EXPECT_EQ(actualExitCode, expectedExitCode) << "Exit code mismatch in " << test.name;
}

#ifndef SYSTEM_TEST_DIR
#error "SYSTEM_TEST_DIR not defined"
#endif

std::vector<SystemTestCase> discoverSystemTests(const fs::path& root) {
    std::vector<SystemTestCase> cases;
    for(const auto& entry: fs::directory_iterator(root)) {
        if(entry.is_directory()) {
            cases.push_back({entry.path().filename().string(), entry.path()});
        }
    }
    return cases;
}

INSTANTIATE_TEST_SUITE_P(SystemTests,
                         SystemTest,
                         ::testing::ValuesIn(discoverSystemTests(SYSTEM_TEST_DIR)),
                         [](const ::testing::TestParamInfo<SystemTest::ParamType>& info) {
                             return info.param.name;
                         });
