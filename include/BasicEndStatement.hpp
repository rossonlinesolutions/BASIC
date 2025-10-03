#pragma once

#include <BasicStatement.hpp>

class BasicEndStatement : public BasicStatement {
    protected:
    std::string property_string() const override;

    public:
    BasicEndStatement() : BasicStatement {"EndStatement"} {
    }

    int execute(BasicConsole& console, BasicEnv& env) const override;
};
