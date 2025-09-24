#include <BasicPrintStatement.hpp>

std::string BasicPrintStatement::property_string() const {
    std::string res;

    for(auto& p: this->expr_list) {
        res += p->to_string();
        res += ",";
    }

    if(!res.empty() && res.back() == ',')
        res.pop_back();

    return res;
}

int BasicPrintStatement::execute(BasicConsole& console, BasicEnv& env) const {
    std::string res = "";

    for(auto& expr: this->expr_list) {
        int r = expr->eval(env);

        res.push_back(r);
    }

    console.printLine(res);
    return 0;
}