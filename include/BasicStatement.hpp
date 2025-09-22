#pragma once

#include <BasicConsole.hpp>
#include <BasicEnv.hpp>
#include <string>

class BasicStatement {
    private:
    const std::string className;

    protected:
    virtual std::string property_string() const = 0;

    public:
    explicit BasicStatement(const std::string className) : className(className) {
    }

    virtual ~BasicStatement()                                       = default;
    virtual int execute(BasicConsole& console, BasicEnv& env) const = 0;

    inline std::string to_string() const {
        return className + "{" + this->property_string() + "}";
    }
};
