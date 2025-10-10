#pragma once

#include <BasicConsole.hpp>
#include <BasicEnv.hpp>
#include <BasicExpression.hpp>
#include <BasicStatement.hpp>
#include <list>

class BasicInputStatement : public BasicStatement {
    private:
    std::list<BasicExpression::Variable> vars;

    public:
    BasicInputStatement(std::list<BasicExpression::Variable> vars) : BasicStatement {"INPUT"}, vars(std::move(vars)) {
    }
    int execute(BasicConsole& console, BasicEnv& env) const override;

    protected:
    std::string property_string() const override;
};
