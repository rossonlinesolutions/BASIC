#include <BasicLetStatement.hpp>

std::string BasicLetStatement::property_string() const {
    std::string res;

    if(std::holds_alternative<char>(this->variable)) {
        res += std::get<char>(this->variable);
    } else {
        res += std::get<std::unique_ptr<BasicExpression>>(this->variable)->to_string();
    }
    res += ",";
    res += this->expr->to_string();
    return res;
}

int BasicLetStatement::execute(BasicConsole& console, BasicEnv& env) const {
    int res = this->expr->eval(env);

    if(std::holds_alternative<char>(this->variable)) {
        env.set(std::get<char>(this->variable), res);
    } else {
        int value = std::get<std::unique_ptr<BasicExpression>>(this->variable)->eval(env);

        if(value < 0 || value > 25) {
            throw std::string {VAR_OUT_OF_BOUNDS};
        }

        env.set(value, res);
    }

    return 0;
}
