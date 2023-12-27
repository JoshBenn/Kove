#pragma once

#include "../include/integer_variables.hpp"
#include "../include/string_variables.hpp"

class VariableDeclarationNode : public ASTNode {
public:
  std::string variableName;
  std::unique_ptr<ASTNode> variable;

  VariableDeclarationNode(std::string &name, std::unique_ptr<ASTNode> type)
      : variableName(name), variable(std::move(type)) {}

  void display(int depth);
};
