#pragma once

#include <BasicConsole.hpp>
#include <list>
#include <string>

class BasicEnv {
    private:
    int env[26];
    std::list<int> callStack;
    std::string stdin_buffer;

    public:
    int get(int v) const;
    void set(int v, int val);
    void pushCurrLine(int line);
    int popReturnAddress();
    char nextStdin(BasicConsole& console);
};
