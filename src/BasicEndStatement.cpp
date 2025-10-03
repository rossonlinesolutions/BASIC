#include <BasicEndStatement.hpp>

std::string BasicEndStatement::property_string() const {
    return "";
}

int BasicEndStatement::execute(BasicConsole& console, BasicEnv& env) const {
    return -2;
}
