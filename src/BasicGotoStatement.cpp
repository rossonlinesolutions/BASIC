#include <BasicGotoStatement.hpp>

std::string BasicGotoStatement::property_string() const {
    return this->expr->to_string();
}

int BasicGotoStatement::execute(BasicConsole& console, BasicEnv& env) const {
    int res = this->expr->eval(env);

    // negative lines are error
    if(res < 0)
        return -1;

    return res;
}
