#pragma once

#include <string>

class BasicConsole {
    public:
    virtual std::string* nextLine()              = 0;
    virtual void printLine(const std::string& s) = 0;
    virtual ~BasicConsole()                      = default;
};
