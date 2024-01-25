// import lexer;

#include <iostream>
#include <vector>
#include <string>

#include "lexer.cpp"

std::string tokenTranslate(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER:         return "IDENTIFIER";
        case TokenType::KEYWORD:            return "KEYWORD";
        case TokenType::STRING_LITERAL:     return "STRING_LITERAL";
        case TokenType::CHARACTER_LITERAL:  return "CHARACTER_LITERAL";
        case TokenType::INTEGER_LITERAL:    return "INTEGER_LITERAL";
        case TokenType::FLOAT_LITERAL:      return "FLOAT_LITERAL";
        case TokenType::BOOLEAN_LITERAL:    return "BOOLEAN_LITERAL";
        case TokenType::OPERATOR:           return "OPERATOR";
        case TokenType::DELIMITER:          return "DELIMITER";
        case TokenType::COMMENT:            return "COMMENT";
        case TokenType::MULTI_COMMENT:      return "MULTI_COMMENT";
        case TokenType::DOCUMENT:           return "DOCUMENT";
        case TokenType::TYPE_ANNOTATION:    return "TYPE_ANNOTATION";
        case TokenType::REFERENCE:          return "REFERENCE";
        case TokenType::OWNERSHIP:          return "OWNERSHIP";
        case TokenType::MODIFIER:           return "MODIFIER";
        case TokenType::ARRAY_LITERAL:      return "ARRAY_LITERAL";
        case TokenType::TUPLE_LITERAL:      return "TUPLE_LITERAL";
        case TokenType::DECORATOR:          return "DECORATOR";
        case TokenType::ERROR:              return "ERROR";
        case TokenType::UNKNOWN:            return "UNKNOWN";
        default:                            return "UNRECOGNIZED";
    }
}

int main() {
    std::vector<std::string> test{
        "var x = 5;",
        "cnst var y: i32 = 10;",
        "let z = 1_234_513_523;",
        "fn main() { let z = \"hey mama\"; }",
        "fn foo(x: isize:>) -> int { loop { break; } }",
        R"(var string: str = "Ryan's a lil' slut dragon";)",
        "fn calculate(x: int, y: <:uint) -> int { return x + y; }",
        "var flag: bool = true && false;",
        "if (x > 5) { x = 5; } else { x = 10; }",
        "for (var i = 0; i < 10; i++) { print(i); }",
        "switch (x) { case 1: break; default: break; }",
        R"(var multilineString: str = "Line1\nLine2\nLine3";)",
        "var arr: [int] = [1, 2, 3, 4, 5];",
        "var tuple: (int, str) = (1, \"hello\");",
        "// This is a comment",
        R"(/* Multi-line comment \n line 2 \n line 3 */)",
        R"(/// This is documentation it goes expandiboi)"
    };

    for (auto t : test) {
        Lexer lexer(t);
        auto tokens = lexer.tokenize();

        for (auto t : tokens) {
            std::string t_str = tokenTranslate(t.type);
            if (t_str.length() < 8) {
                std::printf("Token: %s,\t\t Value: %s\n", t_str.c_str(), t.value.c_str());
            } else {
                std::printf("Token: %s,\t Value: %s\n", t_str.c_str(), t.value.c_str());
            }
        }
        std::cout << std::endl;
    }
}