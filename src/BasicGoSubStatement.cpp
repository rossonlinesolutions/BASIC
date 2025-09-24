#include <BasicGoSubStatement.hpp>

std::string BasicGoSubStatement::property_string() const {
    return this->expr->to_string();
}

int BasicGoSubStatement::execute(BasicConsole& console, BasicEnv& env) const {
    int res = this->expr->eval(env);

    // no negative line
    if(res < 0)
        return -1;

    // push to call stack and go
    env.pushCurrLine();
    return res;
}
