#include <BasicExecutor.hpp>
#include <BasicInterpreter.hpp>
#include <BasicRunStatement.hpp>
#include <iostream>
#include <optional>

std::optional<BasicTokenType> BasicInterpreter::emit(const std::string& s) {
    this->next_line++;

    auto ots = this->lex(s);
    if(ots == std::nullopt) {
        this->semanticErrs++;
        return std::nullopt;
    }

    auto ts = ots.value();
    if(ts.empty())
        return std::nullopt;

    if(!ts.empty() && ts.front().typ == BasicTokenType::INT_LITERAL) {
        this->next_line = ts.front().ival;
        ts.pop_front();
    }

    // if next token is REM, return
    if(!ts.empty() && ts.front().typ == BasicTokenType::REM) {
        this->lines.erase(this->next_line);
        return BasicTokenType::REM;
    }

    // if next token is EXIT, return
    if(!ts.empty() && ts.front().typ == BasicTokenType::EXIT) {
        return BasicTokenType::EXIT;
    }

    std::optional<BasicTokenType> ttyp = ts.empty() ? std::nullopt : std::optional {ts.front().typ};

    // parse
    auto stmt = this->parse(ts);
    if(stmt == nullptr) {
        this->semanticErrs++;
        return ttyp;
    }

    bool runCode = (dynamic_cast<BasicRunStatement*>(stmt.get()) != nullptr);

    if(runCode) {
        int res = 0;
        try {
            res = this->run();
        } catch(const std::string& s) {
            if(s == DIVISION_BY_ZERO) {
                res = -1;
                console.printLine("Execution aborted: Division by zero.");
            } else {
                throw s;
            }
        }
        if(res == -1) {
            this->runtimeErrs++;
        }
    } else {
        // if not a RunStatement, store the line
        this->lines[this->next_line] = std::move(stmt);
    }

    return ttyp;
}

void BasicInterpreter::runInteractive() {
    while(true) {
        std::string* input = this->console.nextLine();
        if(!input)
            return;

        std::string src = *input;
        delete input;

        // check if an exit has been reached
        auto stmt_type = this->emit(src);

        if(stmt_type == BasicTokenType::EXIT)
            return;
    }
}

std::pair<int, std::optional<BasicStatement*>> BasicInterpreter::getStatementAt(int addr) const {
    BasicStatement* stmt = nullptr;
    int curr_line        = 0;
    for(auto& p: this->lines) {
        if(p.first == addr)
            return {addr, p.second.get()};

        if(p.first > addr && (curr_line == 0 || p.first < curr_line)) {
            curr_line = p.first;
            stmt      = p.second.get();
        }
    }

    if(stmt)
        return {curr_line, stmt};

    return {-1, std::nullopt};
}

int BasicInterpreter::run() {
    BasicExecutor executor {*this};
    return executor.run() < 0 ? -1 : 0;
}

std::optional<std::list<BasicToken>> BasicInterpreter::lex(const std::string& s) const {
    BasicLexer lexer {this->console, s};
    lexer.run();

    if(lexer.hasError())
        return std::nullopt;

    return lexer.tokens;
}

std::unique_ptr<BasicStatement> BasicInterpreter::parse(BasicTokenList& tokens) const {
    BasicParser parser;
    return parser.parseLine(this->console, tokens);
}
