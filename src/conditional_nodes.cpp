// #include <iostream>

#include "../include/ast_node.hpp"

///If Statement
class IfStatementNode : public ASTNode {
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> trueBranch;
    std::unique_ptr<ASTNode> falseBranch;

public:
    IfStatementNode(std::unique_ptr<ASTNode> cnd, std::unique_ptr<ASTNode> tBranch, std::unique_ptr<ASTNode> fBranch)
        : condition(std::move(cnd)), trueBranch(std::move(tBranch)), falseBranch(std::move(fBranch)) {}

    void display(int depth = 0) const override {
        std::string indent(depth * 2, ' ');
        std::cout << indent << "IfStatement" << std::endl;
    }
};
