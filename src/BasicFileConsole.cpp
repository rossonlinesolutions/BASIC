#pragma once

#include <BasicFileConsole.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>

std::string basic_read_file_reversed(const std::string& filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if(!file)
        return "";
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::reverse(content.begin(), content.end());
    return content;
}

std::string* BasicFileConsole::nextLine() {
    if(this->content.empty())
        return nullptr;

    auto* line = new std::string();

    while(!content.empty() && content.back() != '\n' && content.back() != '\r') {
        line->push_back(this->content.back());
        this->content.pop_back();
    }

    if(!this->content.empty())
        this->content.pop_back();

    if(!content.empty() && content.back() == '\r')
        this->content.pop_back();

    return line;
}

void BasicFileConsole::printLine(const std::string& s) {
    std::cout << s << std::endl;
}

void BasicFileConsole::setContent(const std::string& content) {
    this->content = std::string(content.rbegin(), content.rend());
}

std::string* BasicFileConsole::readStdin() {
    std::string line;
    if(!std::getline(std::cin, line)) {
        return nullptr;
    }
    return new std::string(line);
}
