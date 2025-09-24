#include <BasicLetStatement.hpp>

std::string BasicLetStatement::property_string() const {
    std::string res;
    res += this->variable;
    res += ",";
    res += this->expr->to_string();
    return res;
}

int BasicLetStatement::execute(BasicConsole& console, BasicEnv& env) const {
    int res = this->expr->eval(env);
    env.set(this->variable, res);
    return 0;
}
