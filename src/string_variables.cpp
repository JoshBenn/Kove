#include "../include/string_variables.hpp"

//function to append to the back of the string
void StringNode::append(std::string& str) {
    value.append(str);
    length = value.length();
}

void StringNode::prepend(std::string& str) {
    value = str + value;
    length = value.length();
}

bool StringNode::contains(std::string& str) {
    return value.find(str) != std::string::npos;
}

void StringNode::reverse() {
    std::reverse(value.begin(), value.end());
}

std::vector<std::string> StringNode::split() {
    std::vector<std::string> str_set;
    std::string str = "";

    for(size_t i  = 0; i < length; ++i) {
        if (value[i] == ' ') {
            if (!str.empty()) {
                str_set.push_back(str);
                str = "";
            }
            continue;
        }
        str += value[i];
    }

    if (!str.empty()) {
        str_set.push_back(str);
    }

    return str_set;
}

std::vector<std::string> StringNode::split(char ch) {
    std::vector<std::string> str_set;
    std::string str = "";

    for(size_t i  = 0; i < length; ++i) {
        if (value[i] == ch) {
            if (!str.empty()) {
                str_set.push_back(str);
                str = "";
            }
            continue;
        }
        str += value[i];
    }

    if (!str.empty()) {
        str_set.push_back(str);
    }

    return str_set;
}

size_t StringNode::size() {
    return length;
}

void StringNode::display(int depth) const {
    std::cout << value;
}
