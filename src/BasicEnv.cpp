#include <BasicEnv.hpp>

int BasicEnv::get(int v) const {
    return this->env[v - 'A'];
}

void BasicEnv::set(int v, int val) {
    this->env[v - 'A'] = val;
}

void BasicEnv::pushCurrLine(int line) {
    this->callStack.push_front(line);
}

int BasicEnv::popReturnAddress() {
    if(this->callStack.empty()) {
        return -1;
    }

    int ret = this->callStack.front();
    this->callStack.pop_front();
    return ret;
}
