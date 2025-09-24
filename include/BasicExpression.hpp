#pragma once

#include <BasicEnv.hpp>
#include <list>
#include <memory>
#include <string>

class BasicExpression {
    private:
    const std::string className;

    protected:
    virtual std::string property_string() = 0;

    public:
    virtual ~BasicExpression() = default;

    BasicExpression(const std::string& className) : className(className) {
    }
    virtual int eval(BasicEnv& env) const = 0;

    inline std::string to_string() {
        return className + "{" + this->property_string() + "}";
    }
};

using BasicExpressionList = std::list<std::unique_ptr<BasicExpression>>;
