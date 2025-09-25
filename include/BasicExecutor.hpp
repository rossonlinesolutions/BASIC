#pragma once

#include <BasicInterpreter.hpp>

class BasicExecutor {
    BasicInterpreter& interpreter;
    int curr_line = 0;

    public:
    BasicExecutor(BasicInterpreter& interpreter) : interpreter(interpreter) {
    }

    int run();

    private:
    int executeLine();
};