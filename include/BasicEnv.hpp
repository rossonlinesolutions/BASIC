#pragma once

#include <BasicConsole.hpp>
#include <list>
#include <string>

class BasicEnv {
    private:
    int env[26];
    std::list<int> callStack;
    std::string stdin_buffer;
    int curr_line = 0;

    public:
    inline void set_line(int line) {
        this->curr_line = line;
    }

    inline int get_line() {
        return this->curr_line;
    }

    int get(int v) const;
    void set(int v, int val);
    void pushCurrLine();
    int popReturnAddress();
    char nextStdin(BasicConsole& console);
};

#define DIVISION_BY_ZERO  "Division by Zero."
#define VAR_OUT_OF_BOUNDS "Var index out of bounds."
#define UNPARSED_END      "Error: found unparsed junk at end."
