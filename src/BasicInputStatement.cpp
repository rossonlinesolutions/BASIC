#pragma once

#include <BasicInputStatement.hpp>

std::string BasicInputStatement::property_string() const {
    std::string outp;
    for(auto& c: this->vars) {
        outp += c;
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

        env.set(c, nxt);
    }

    return 0;
}
