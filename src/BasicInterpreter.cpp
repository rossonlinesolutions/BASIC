#include <BasicExecutor.hpp>
#include <BasicInterpreter.hpp>
#include <BasicRunStatement.hpp>
#include <iostream>

void BasicInterpreter::emit(const std::string& s) {
    this->next_line++;
    if(s.find("REM") != std::string::npos) {
        return;
    }

    auto ots = this->lex(s);
    if(ots == std::nullopt) {
        this->semanticErrs++;
        return;
    }

    auto ts = ots.value();
    if(!ts.empty() && ts.front().typ == BasicTokenType::INT_LITERAL) {
        this->next_line = ts.front().ival;
        ts.pop_front();
    }

    // parse
    auto stmt = this->parse(ts);
    if(stmt == nullptr) {
        this->semanticErrs++;
        return;
    }

    bool runCode = (dynamic_cast<BasicRunStatement*>(stmt.get()) != nullptr);

    this->lines[this->next_line] = std::move(stmt);

    if(runCode) {
        int res = this->run();
        if(res == -1) {
            this->runtimeErrs++;
        }
    }
}

void BasicInterpreter::runInteractive() {
    while(true) {
        std::string* input = this->console.nextLine();
        if(!input)
            return;
        bool exit = input->find("EXIT") != std::string::npos;
        exit      = exit || input->find("exit") != std::string::npos;
        exit      = exit || input->find("quit") != std::string::npos;
        exit      = exit || input->find("QUIT") != std::string::npos;
        if(exit)
            return;

        std::string src = *input;
        delete input;

        this->emit(src);
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
