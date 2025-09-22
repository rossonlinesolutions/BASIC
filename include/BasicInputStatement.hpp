#pragma once

#include <BasicConsole.hpp>
#include <BasicEnv.hpp>
#include <BasicStatement.hpp>
#include <list>

class BasicInputStatement : public BasicStatement {
    private:
    std::list<char> vars;

    public:
    BasicInputStatement(const std::list<char>& vars) : BasicStatement {"INPUT"}, vars(vars) {
    }
    int execute(BasicConsole& console, BasicEnv& env) const override;

    protected:
    std::string property_string() const override;
};
