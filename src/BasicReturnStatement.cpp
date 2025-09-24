#include <BasicReturnStatement.hpp>

std::string BasicReturnStatement::property_string() const {
    return "";
}

int BasicReturnStatement::execute(BasicConsole& console, BasicEnv& env) const {
    return env.popReturnAddress();
}
