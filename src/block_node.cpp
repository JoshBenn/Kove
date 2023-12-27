#include "ast_node.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/// Block
class BlockNode : public ASTNode {
  std::vector<std::unique_ptr<ASTNode>> statements;

public:
  BlockNode(std::vector<std::unique_ptr<ASTNode>> stmts)
      : statements(std::move(stmts)) {}

  void display(int depth = 0) const override {
    std::string indent(depth * 2, ' ');
    std::cout << indent << "Block:" << std::endl;
    for (const auto &stmt : statements) {
      stmt->display(depth + 1);
    }
  }
};
