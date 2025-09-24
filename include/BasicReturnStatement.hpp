#pragma once

#include <BasicStatement.hpp>

class BasicReturnStatement : public BasicStatement {
    protected:
    std::string property_string() const override;

    public:
    BasicReturnStatement() : BasicStatement {"ReturnStatement"} {
    }

    int execute(BasicConsole& console, BasicEnv& env) const override;
};
