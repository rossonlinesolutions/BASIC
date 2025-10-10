#include <BasicVarExpression.hpp>

std::string BasicVarExpression::property_string() {
    std::string res;

    if(std::holds_alternative<char>(this->value)) {
        res.push_back(std::get<char>(this->value));
    } else {
        res += std::get<std::unique_ptr<BasicExpression>>(this->value)->to_string();
    }
    return res;
}

int BasicVarExpression::eval(BasicEnv& env) const {
    if(std::holds_alternative<char>(this->value)) {
        return env.get(std::get<char>(this->value));
    }

    // else get expression
    auto& expr = std::get<std::unique_ptr<BasicExpression>>(this->value);
    int value  = expr->eval(env);

    if(value < 0 || value > 25) {
        throw std::string {VAR_OUT_OF_BOUNDS};
    }

    return env.get(value);
}
