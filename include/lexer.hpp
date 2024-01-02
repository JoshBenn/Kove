#pragma once

#include <string>
#include <vector>
#include <regex>
#include <cctype>
#include <functional>

enum class TokenType {
    VARIABLE_DECLARATION, INTEGER_LITERAL, STRING_LITERAL, TYPE_SPECIFIER, EXPRESSION, OPERATOR, KEYWORD, END_OF_FILE, UNKNOWN,
};

struct Token {
    TokenType general_type;
    std::string value;
};

class Lexer {
    std::string input;
    size_t position;

public:
    Lexer(const std::string& input) : input(input), position(0) {}

    //Tokenization logic
    std::vector<Token> tokenize(); 

private:
    std::string readWhile(std::function<bool(char)> predicate);
};


