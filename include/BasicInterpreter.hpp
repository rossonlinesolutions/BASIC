#pragma once

#include <BasicConsole.hpp>
#include <BasicEnv.hpp>
#include <BasicLexer.hpp>
#include <BasicParser.hpp>
#include <BasicStatement.hpp>
#include <BasicToken.hpp>
#include <map>
#include <memory>
#include <optional>
#include <string>

class BasicInterpreter {
    int next_line    = 0;
    int runs         = 0;
    int semanticErrs = 0;
    int runtimeErrs  = 0;
    std::map<int, std::unique_ptr<BasicStatement>> lines;

    public:
    BasicEnv env;
    BasicConsole& console;
    BasicInterpreter(BasicConsole& console) : console(console) {
    }

    inline int getRuns() {
        return this->runs;
    }

    inline int getSemanticErrs() {
        return this->semanticErrs;
    }

    inline int getRuntimeErrs() {
        return this->runtimeErrs;
    }

    inline int getTotalErrs() {
        return this->getRuntimeErrs() + this->getSemanticErrs();
    }

    std::optional<BasicTokenType> emit(const std::string& s);
    std::pair<int, std::optional<BasicStatement*>> getStatementAt(int addr) const;
    void runInteractive();

    private:
    int run();
    std::optional<std::list<BasicToken>> lex(const std::string& s) const;
    std::unique_ptr<BasicStatement> parse(BasicTokenList& tokens) const;
};
