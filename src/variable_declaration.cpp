#include "../include/variable_declaration.hpp"
#include <iostream>

/// Declaration of a variable
void VariableDeclarationNode::display(int depth) const {
    std::string indent(depth * 2, ' ');

    std::cout << indent << "VariableDeclarations: " << variableName;
    std::cout << " = ";
    variable->display();
    std::cout << std::endl;
};
