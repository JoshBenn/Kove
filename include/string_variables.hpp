#pragma once


#include <algorithm>
#include <vector>


#include "../include/ast_node.hpp"

class StringNode : public ASTNode {
private:
    std::string value;
    size_t length;

public:
    explicit StringNode(std::string str) : value(str), length(str.length()) {}

    //function to append to the back of the string
    void append(std::string& str);
    void prepend(std::string& str);
    bool contains(std::string& str);
    void reverse();
    std::vector<std::string> split();
    std::vector<std::string> split(char ch);
    size_t size();

    void display(int depth = 0) const override;
};
