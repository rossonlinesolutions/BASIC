#include <BasicUnaryExpression.hpp>

std::string BasicUnaryExpression::property_string() {
    std::string res = std::to_string(this->isMinus) + ",";
    res += this->expr->to_string();
    return res;
}

int BasicUnaryExpression::eval(BasicEnv& env) const {
    int res = this->expr->eval(env);

    if(this->isMinus)
        res *= (-1);

    return res;
}
