#pragma once

#include <BasicStatement.hpp>

class BasicRunStatement : public BasicStatement {
    protected:
    std::string property_string() const override;

    public:
    BasicRunStatement() : BasicStatement {"RunStatement"} {
    }

    int execute(BasicConsole& console, BasicEnv& env) const override;
};
