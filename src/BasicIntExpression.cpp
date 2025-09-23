#include <BasicIntExpression.hpp>

std::string BasicIntExpression::property_string() {
    return std::to_string(this->value);
}

int BasicIntExpression::eval(BasicEnv& env) const {
    return this->value;
}
