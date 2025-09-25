#include <BasicExecutor.hpp>

int BasicExecutor::run() {
    int res = 0;
    while(res == 0) {
        res = this->executeLine();
    }

    if(res == -1)
        return -1;
    return 0;
}

int BasicExecutor::executeLine() {
    auto stmt = this->interpreter.getStatementAt(curr_line);
    curr_line++;
    if(stmt.first == -1)
        return 1;

    int result = stmt.second.value()->execute(this->interpreter.console, this->interpreter.env);

    if(result <= 0)
        return result;

    // else set line
    this->curr_line = result;
    return 0;
}
