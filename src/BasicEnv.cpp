#include <BasicConsole.hpp>
#include <BasicEnv.hpp>

int BasicEnv::get(int v) const {
    if(v >= 'A') {
        v -= 'A';
    }
    return this->env[v];
}

void BasicEnv::set(int v, int val) {
    if(v >= 'A') {
        v -= 'A';
    }
    this->env[v] = val;
}

void BasicEnv::pushCurrLine() {
    this->callStack.push_front(this->curr_line);
}

int BasicEnv::popReturnAddress() {
    if(this->callStack.empty()) {
        return -1;
    }

    int ret = this->callStack.front();
    this->callStack.pop_front();
    return ret;
}

char BasicEnv::nextStdin(BasicConsole& console) {
    // if buffer is still not empty, return content
    if(!this->stdin_buffer.empty()) {
        char ret = this->stdin_buffer.back();
        this->stdin_buffer.pop_back();
        return ret;
    }

    // else request one more line
    std::string* input = console.readStdin();

    // EOF
    if(input == nullptr)
        return -1;

    // set buffer reversed
    this->stdin_buffer = std::string {input->rbegin(), input->rend()};
    delete input;

    // rerun
    return this->nextStdin(console);
}
