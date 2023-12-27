#include <memory>
#include <stdexcept>

#include "../include/variable_declaration.hpp"
#include <variable_declaration.hpp>

/// Parser itself
using std::make_unique;

class Parser {
  std::vector<Token> tokens;
  size_t currentPosition;

public:
  explicit Parser(std::vector<Token> tkns)
      : tokens(std::move(tkns)), currentPosition(0) {}

  std::unique_ptr<ASTNode> parse() {
    // Parsing function(s)
    std::unique_ptr<ASTNode> rootNode;

    while (peek().general_type != TokenType::END_OF_FILE) {
      if (peek().general_type == TokenType::VARIABLE_DECLARATION) {
        rootNode = parseVariableDeclaration();
        // Handle the parsed variable declaration
      }
      // Add more cases for other constructs
    }

    return rootNode;
  }

private:
  const Token &peek() const { return tokens[currentPosition]; }

  // Consume & return current token
  Token consume(TokenType expectedType) {
    if (tokens[currentPosition].general_type != expectedType) {
      throw std::runtime_error("Unexpected token type");
    }
    return tokens[currentPosition++];
  }

  std::unique_ptr<ASTNode> parseVariableDeclaration() {
    // var or const
    auto varToken = consume(TokenType::VARIABLE_DECLARATION);

    // Variable name
    auto nameToken = consume(TokenType::EXPRESSION);
    Token varType;
    // Type annotation
    std::unique_ptr<ASTNode> typeNode;
    if (peek().general_type == TokenType::TYPE_SPECIFIER) {
      varType = consume(TokenType::TYPE_SPECIFIER);
    } else {
      // TODO: Auto infer type -- Current: default int
      varType = Token{TokenType::TYPE_SPECIFIER, "int"};
    }

    consume(TokenType::OPERATOR);                    // Expect '='
    auto initValue = consume(TokenType::EXPRESSION); // Expect the expression
    consume(TokenType::OPERATOR);                    // Expect ';'

    typeNode = createTypeNode(varType, initValue);

    return make_unique<VariableDeclarationNode>(nameToken.value,
                                                std::move(typeNode));
  }

  std::unique_ptr<ASTNode> createTypeNode(const Token &typeSpecifierToken,
                                          const Token &value) {
    auto it = node_mapper.find(typeSpecifierToken.value);
    if (it != node_mapper.end()) {
      return it->second(value);
    }
    throw std::runtime_error("Unknown type specifier: " +
                             typeSpecifierToken.value);
  }

  std::unique_ptr<ASTNode> parseExpression() {
    // Parse an expression
    auto left = parsePrimaryExpression();

    // while (peek().general_type == TokenType::OPERATOR) {
    //     auto operatorToken = consume(TokenType::OPERATOR);

    //     if (operatorToken.data.operatorType == OperatorType::PLUS ||
    //         operatorToken.data.operatorType == OperatorType::MINUS ||
    //         operatorToken.data.operatorType == OperatorType::ASTERISK ||
    //         operatorToken.data.operatorType == OperatorType::SLASH) {

    //         auto right = parsePrimaryExpression();
    //         left = std::make_unique<BinaryExpressionNode>(std::move(left),
    //         operatorToken.data.operatorType, std::move(right));
    //     } else {
    //         throw std::runtime_error("Unsupported opearator in expression");
    //     }
    // }

    return left;
  }

  std::unique_ptr<ASTNode> parsePrimaryExpression() {
    // Integer Literal
    if (peek().general_type == TokenType::INTEGER_LITERAL) {
      auto token = consume(TokenType::INTEGER_LITERAL);
      return std::make_unique<IntNode>(std::stoi(token.value));
    } else if (peek().general_type == TokenType::EXPRESSION) {
      // TODO: IMPLEMENT
      auto token = consume(TokenType::EXPRESSION);
    }

    // If none of the above, throw an error
    throw std::runtime_error("Expected primary expression");
  }

  // std::unique_ptr<ASTNode> parseBlock() {
  //     if (peek().general_type == TokenType::OPERATOR &&
  //     peek().data.operatorType == OperatorType::OPEN_BRACE) {
  //         consume(TokenType::OPERATOR); //expect '{'

  //         std::vector<std::unique_ptr<ASTNode>> statements;

  //         while (peek().general_type != TokenType::OPERATOR ||
  //         peek().data.operatorType != OperatorType::CLOSE_BRACE) {
  //             //Parse inside the block
  //             if (peek().general_type == TokenType::VARIABLE_DECLARATION) {
  //                 statements.push_back(parseVariableDeclaration());
  //             }
  //             //Add more later
  //         }

  //         consume(TokenType::OPERATOR); //expect '}'

  //         //Return a blocknode
  //         return std::make_unique<BlockNode>(std::move(statements));
  //     } else {
  //         throw std::runtime_error("Expected '{' at the beginning of a
  //         block");
  //     }
  // }

  // std::unique_ptr<ASTNode> parseIfStatement() {
  //     consume(TokenType::KEYWORD); //consume IF

  //     //Parse condition
  //     auto condition = parseExpression();

  //     //Parse truthy
  //     auto trueBranch = parseBlock();

  //     //Parse falsy
  //     std::unique_ptr<ASTNode> elseBranch = nullptr;
  //     if (peek().general_type == TokenType::KEYWORD && peek().value ==
  //     "else") {
  //         consume(TokenType::KEYWORD); //Consume ELSE
  //         elseBranch = parseBlock();
  //     }

  //     return std::make_unique<IfStatementNode>(std::move(condition),
  //     std::move(trueBranch), std::move(elseBranch));
  // }

  // Other parsing functions
};

extern void map_nodes() {
  std::map<std::string, NodeCreator> int_nodes{
      {"int",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<IntNode>(std::stoi(token.value));
       }},
      {"i8",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<I8Node>(std::stoi(token.value));
       }},
      {"i16",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<I16Node>(std::stoi(token.value));
       }},
      {"i32",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<I32Node>(std::stoi(token.value));
       }},
      {"i64",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<I64Node>(std::stoi(token.value));
       }},
      {"uint",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<UIntNode>(std::stoi(token.value));
       }},
      {"u8",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<U8Node>(std::stoi(token.value));
       }},
      {"u16",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<U16Node>(std::stoi(token.value));
       }},
      {"u32",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<U32Node>(std::stoi(token.value));
       }},
      {"u64",
       [](const Token &token) -> std::unique_ptr<ASTNode> {
         return std::make_unique<U64Node>(std::stoi(token.value));
       }},
  };
}

/// Test
int main() {
  std::vector<std::string> testInputs{
      "var x = 5;", "var y: i32 = 10;", "const z = 123456789;",
      // "if (x > y) { x = 10; }",
  };
  map_nodes();

  for (const auto &code : testInputs) {
    Lexer lexer(code);
    auto tokens = lexer.tokenize();

    for (const auto &token : tokens) {
      std::printf("Token: %d, Value %s\n", static_cast<int>(token.general_type),
                  token.value.c_str());
    }

    Parser parser(tokens);
    auto ast = parser.parse();

    std::cout << "AST for \"" << code << "\":" << std::endl;
    if (ast) {
      ast->display();
    } else {
      std::cout << "No AST generated" << std::endl;
    }

    std::cout << "---------------------" << std::endl;
  }

  return 0;
}
