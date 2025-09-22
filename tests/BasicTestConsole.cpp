#include "BasicTestConsole.hpp"

std::string* BasicTestConsole::nextLine() {
    if(this->src.empty())
        return nullptr;

    size_t pos       = this->src.find('\n');
    std::string* ret = new std::string {""};

    if(pos == std::string::npos) {
        ret->append(this->src);
        src.clear();
    } else {
        ret->append(this->src.substr(0, pos));
        this->src = this->src.substr(pos + 1);
    }

    return ret;
}

void BasicTestConsole::printLine(const std::string& s) {
    this->out += s + "\n";
}

std::string* BasicTestConsole::readStdin() {
    if(this->in.empty())
        return nullptr;

    size_t pos       = this->in.find('\n');
    std::string* ret = new std::string {""};

    if(pos == std::string::npos) {
        ret->append(this->in);
        in.clear();
    } else {
        ret->append(this->in.substr(0, pos));
        this->in = this->in.substr(pos + 1);
    }

    return ret;
}
