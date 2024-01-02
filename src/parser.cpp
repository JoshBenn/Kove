#include <memory>
#include <stdexcept>
#include <string>

#include "../include/variable_declaration.hpp"

/// Parser itself
using std::make_unique;

class Parser {
    std::vector<Token> tokens;
    size_t currentPosition;

public:
    explicit Parser(std::vector<Token> tkns) : tokens(std::move(tkns)), currentPosition(0) {}

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
            std::cout << tokens[currentPosition].value << std::endl;
            throw std::runtime_error("Unexpected token type");
        }
        return tokens[currentPosition++];
    }


    //Variable declaration
    std::unique_ptr<ASTNode> parseVariableDeclaration() {
        //Consum var or const
        auto varToken = consume(TokenType::VARIABLE_DECLARATION);

        //Variable name
        auto nameToken = consume(TokenType::EXPRESSION);

        // Type annotation
        Token typeToken;
        std::unique_ptr<ASTNode> typeNode;
        if (peek().general_type == TokenType::OPERATOR && peek().value == ":") {
            consume(TokenType::OPERATOR); //Expect ':'
            typeToken = consume(TokenType::TYPE_SPECIFIER);
        } else {
            // TODO: Auto infer type -- Current: default int
            typeToken = Token{TokenType::TYPE_SPECIFIER, "int"};
        }

        consume(TokenType::OPERATOR); // Expect '='

        //Initialize based on type
        Token valueToken;
        if (typeToken.value == "string") { //for strings
            valueToken = consume(TokenType::STRING_LITERAL); // Expect the expression
        } else {
            valueToken = consume(TokenType::INTEGER_LITERAL); // Expect the expression
        }

        //Consume ';'
        consume(TokenType::OPERATOR); 

        std::unique_ptr<ASTNode> initializer = createTypeNode(typeToken, valueToken);

        return make_unique<VariableDeclarationNode>(nameToken.value, std::move(typeNode));
    }

    
    std::unique_ptr<ASTNode> createTypeNode(const Token &typeSpecifierToken, const Token &valueToken) {
        if(typeSpecifierToken.value == "int") {
            return make_unique<IntNode<int>>(static_cast<int>(std::stoi(valueToken.value)));
        } 
        if (typeSpecifierToken.value == "i8"){
            return make_unique<IntNode<int8_t>>(static_cast<int8_t>(std::stoi(valueToken.value)));
        }
        if (typeSpecifierToken.value == "i16"){
            return make_unique<IntNode<int16_t>>(static_cast<int16_t>(std::stoi(valueToken.value)));
        }
        if (typeSpecifierToken.value == "i32"){
            return make_unique<IntNode<int32_t>>(static_cast<int32_t>(std::stoi(valueToken.value)));
        }
        if (typeSpecifierToken.value == "i64"){
            return make_unique<IntNode<int64_t>>(static_cast<int64_t>(std::stoi(valueToken.value)));
        }
        if(typeSpecifierToken.value == "uint") {
            return make_unique<IntNode<unsigned int>>(static_cast<unsigned int>(std::stoi(valueToken.value)));
        } 
        if (typeSpecifierToken.value == "u8"){
            return make_unique<IntNode<uint8_t>>(static_cast<uint8_t>(std::stoi(valueToken.value)));
        }
        if (typeSpecifierToken.value == "u16"){
            return make_unique<IntNode<uint16_t>>(static_cast<uint16_t>(std::stoi(valueToken.value)));
        }
        if (typeSpecifierToken.value == "u32"){
            return make_unique<IntNode<uint32_t>>(static_cast<uint32_t>(std::stoi(valueToken.value)));
        }
        if (typeSpecifierToken.value == "u64"){
            return make_unique<IntNode<uint64_t>>(static_cast<uint64_t>(std::stoi(valueToken.value)));
        }
        if (typeSpecifierToken.value == "string") {
            return make_unique<StringNode>(valueToken.value);
        }

        //Type not found
        throw std::runtime_error("Unknown type specifier: " + typeSpecifierToken.value);
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
        //         left =
        //         std::make_unique<BinaryExpressionNode>(std::move(left),
        //         operatorToken.data.operatorType, std::move(right));
        //     } else {
        //         throw std::runtime_error("Unsupported opearator in
        //         expression");
        //     }
        // }

        return left;
    }

    std::unique_ptr<ASTNode> parsePrimaryExpression() {
        // Integer Literal
        if (peek().general_type == TokenType::INTEGER_LITERAL) {
            auto token = consume(TokenType::INTEGER_LITERAL);
            return std::make_unique<IntNode<int>>(std::stoi(token.value));
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

/// Test
int main() {
    std::vector<std::string> testInputs{
        "var x = 5;", 
        "var y: i32 = 10;", 
        "const z = 123456789;",
        R"(var str: string = "Yo dawg";)"
        // "if (x > y) { x = 10; }",
    };

    for (const auto &code : testInputs) {
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        for (const auto &token : tokens) {
            std::printf("Token: %d, Value %s\n",
                        static_cast<int>(token.general_type),
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
