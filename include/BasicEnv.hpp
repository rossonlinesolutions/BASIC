#pragma once

#include <list>

class BasicEnv {
    private:
    int env[26];
    std::list<int> callStack;

    public:
    int get(int v) const;
    void set(int v, int val);
    void pushCurrLine(int line);
    int popReturnAddress();
};
