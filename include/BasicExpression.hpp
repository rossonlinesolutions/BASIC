#pragma once

#include <BasicEnv.hpp>
#include <list>
#include <memory>
#include <string>
#include <variant>

class BasicExpression {
    private:
    const std::string className;

    protected:
    virtual std::string property_string() = 0;

    public:
    using Variable             = std::variant<char, std::unique_ptr<BasicExpression>>;
    virtual ~BasicExpression() = default;

    BasicExpression(const std::string& className) : className(className) {
    }
    virtual int eval(BasicEnv& env) const = 0;

    inline std::string to_string() {
        return className + "{" + this->property_string() + "}";
    }
};

using BasicExpressionList = std::list<std::unique_ptr<BasicExpression>>;
