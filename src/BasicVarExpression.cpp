#include <BasicVarExpression.hpp>

std::string BasicVarExpression::property_string() {
    return "" + this->value;
}

int BasicVarExpression::eval(BasicEnv& env) const {
    return env.get(this->value);
}
