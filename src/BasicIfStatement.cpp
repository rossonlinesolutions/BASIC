#include <BasicIfStatement.hpp>

static std::string basic_relop_string(BasicRelOperation op) {
    switch(op) {
        case BasicRelOperation::LOWER:
            return "LOWER";
        case BasicRelOperation::GREATER:
            return "GREATER";
        case BasicRelOperation::NOT_EQUALS:
            return "NOT_EQUALS";
        case BasicRelOperation::EQUALS:
            return "EQUALS";
        case BasicRelOperation::LOWER_EQUALS:
            return "LOWER_EQUALS";
        default:
            return "GREATER_EQUALS";
    }
}

static bool basic_execute_relop(int left, BasicRelOperation op, int right) {
    switch(op) {
        case BasicRelOperation::EQUALS:
            return left == right;
        case BasicRelOperation::GREATER:
            return left > right;
        case BasicRelOperation::GREATER_EQUALS:
            return left >= right;
        case BasicRelOperation::LOWER:
            return left < right;
        case BasicRelOperation::LOWER_EQUALS:
            return left <= right;
        default:
            return left != right;
    }
}

std::string BasicIfStatement::property_string() const {
    std::string res;
    res += lcondition->to_string();
    res += ",";
    res += basic_relop_string(this->op);
    res += ",";
    res += rcondition->to_string();
    res += ",";
    res += stmt->to_string();
    return res;
}

int BasicIfStatement::execute(BasicConsole& console, BasicEnv& env) const {
    int left  = this->lcondition->eval(env);
    int right = this->rcondition->eval(env);

    // if true then run then branch
    if(basic_execute_relop(left, this->op, right)) {
        return this->stmt->execute(console, env);
    }

    // no else
    return 0;
}
