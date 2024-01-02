#pragma once

#include <cstdint>
#include <memory>

#include "../include/ast_node.hpp"

template <class T> class IntNode : public ASTNode {
private:
    T value;

public:
    explicit IntNode(T val) : value(val) {}

    void display(int depth = 0) const override { std::cout << value; }
};
