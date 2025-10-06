#include <BasicEndStatement.hpp>
#include <BasicExecutor.hpp>

int BasicExecutor::run() {
    int res = 0;
    while(res == 0) {
        res = this->executeLine();
    }

    if(res == -1)
        return -1;

    // if last statement was end, we got -2 and just can continue here
    return 0;
}

int BasicExecutor::executeLine() {
    auto stmt = this->interpreter.getStatementAt(curr_line);
    if(stmt.first == -1)
        return 1;

    // set the next line to the statements line + 1
    curr_line = stmt.first + 1;

    // set the next line such that a GOSUB call would push the return
    // line (not statement of this line, instead next line)
    this->interpreter.env.set_line(curr_line);

    int result = stmt.second.value()->execute(this->interpreter.console, this->interpreter.env);

    if(result <= 0)
        return result;

    // else set line
    this->curr_line = result;
    return 0;
}
