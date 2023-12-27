

#include "../include/ast_node.hpp"

///Binary Expression for mathematics
class BinaryExpressionNode : public ASTNode {
    std::unique_ptr<ASTNode> leftOperand;
    // OperatorType op;
    std::unique_ptr<ASTNode> rightOperand;

public:
    BinaryExpressionNode(std::unique_ptr<ASTNode> left,/* OperatorType oper,*/ std::unique_ptr<ASTNode> right)
        : leftOperand(std::move(left)), /*op(oper),*/ rightOperand(std::move(right)) {}

    void display(int depth = 0) const override {
        std::string indent(depth * 2, ' ');
        std::cout << indent << "BinaryExpression:" << std::endl;
    }
};

