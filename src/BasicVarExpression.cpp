#include <BasicVarExpression.hpp>

std::string BasicVarExpression::property_string() {
    std::string res;
    res.push_back(this->value);
    return res;
}

int BasicVarExpression::eval(BasicEnv& env) const {
    return env.get(this->value);
}
