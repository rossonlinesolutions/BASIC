#pragma once

#include <BasicInputStatement.hpp>

std::string BasicInputStatement::property_string() const {
    std::string outp;
    for(auto& c: this->vars) {
        if(std::holds_alternative<char>(c)) {
            outp += std::get<char>(c);
        } else {
            outp += std::get<std::unique_ptr<BasicExpression>>(c)->to_string();
        }
        outp += ",";
    }

    // remove last ","
    if(!outp.empty() && outp.back() == ',') {
        outp.pop_back();
    }

    return outp;
}

int BasicInputStatement::execute(BasicConsole& console, BasicEnv& env) const {
    for(auto& c: this->vars) {
        char nxt = env.nextStdin(console);

        if(nxt == -1)
            return -1;

        if(std::holds_alternative<char>(c)) {
            env.set(std::get<char>(c), nxt);
        } else {
            int value = std::get<std::unique_ptr<BasicExpression>>(c)->eval(env);

            // error if index out of bounds
            if(value < 0 || value > 25) {
                throw std::string {VAR_OUT_OF_BOUNDS};
            }

            // else set env
            env.set(value, nxt);
        }
    }

    return 0;
}
