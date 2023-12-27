#pragma once

#include "lexer.hpp"
#include <functional>
#include <memory>
#include <iostream>

/// Abstract Syntax Tree
class ASTNode {
public:
  virtual ~ASTNode() = default;
  virtual void display(int depth = 0) const = 0;

  // Common functions
};
