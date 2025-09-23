#include <BasicBinaryExpression.hpp>

static int evaluate_expr(int left, BasicBinOp op, int right) {
    switch(op) {
        case BasicBinOp::PLUS:
            return left + right;
        case BasicBinOp::MINUS:
            return left - right;
        case BasicBinOp::MUL:
            return left * right;
        /* case BasicBinOp::DIV: */
        default:
            return left / right;
    }
}

static std::string binop_to_string(BasicBinOp op) {
    switch(op) {
        case BasicBinOp::PLUS:
            return "PLUS";
        case BasicBinOp::MINUS:
            return "MINUS";
        case BasicBinOp::MUL:
            return "MUL";
        default:
            return "DIV";
    }
}

std::string BasicBinaryExpression::property_string() {
    std::string res;
    res += this->lexpr->to_string();
    res += ",";
    res += this->rexpr->to_string();
    res += ",";
    res += binop_to_string(this->op);

    return res;
}

int BasicBinaryExpression::eval(BasicEnv& env) const {
    int left  = this->lexpr->eval(env);
    int right = this->rexpr->eval(env);

    return evaluate_expr(left, this->op, right);
}
