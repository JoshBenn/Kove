#include "../include/lexer.hpp"



    //Tokenization logic
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (position < input.length()) {
        char current = input[position];

        //Skip whitespaces
        if (isspace(current)) {
            position++;
            continue;
        }

        if (isalpha(current)) {
            std::string value = readWhile([](char ch) { return isalpha(ch) || isdigit(ch); });
            Token token;
            token.value = value;
            

            if (value == "if") {
                token.general_type = TokenType::KEYWORD;
            }
            else if (value == "var" || value == "const") {
                token.general_type = TokenType::VARIABLE_DECLARATION;
            }
            else if (value == "int" || value == "i8" || value == "i16" || value == "i32" || value == "i64" || 
                    value == "uint" || value == "u8" || value == "u16" || value == "u32" || value == "u64" ||
                    value == "string") {
                token.general_type = TokenType::TYPE_SPECIFIER;
            }
            else {
                token.general_type = TokenType::EXPRESSION;
            }

            tokens.push_back(token);
        } 
        else if (isdigit(current)) {
            std::string number = readWhile([](char ch) { return isdigit(ch); });
            tokens.push_back({TokenType::INTEGER_LITERAL, number});
        } 
        else {
            Token token;
            token.value = std::string(1, current);
            token.general_type = TokenType::OPERATOR;

            tokens.push_back(token);
            position++;
        }
    }


    tokens.push_back({TokenType::END_OF_FILE, ""});
    return tokens;
}

std::string Lexer::readWhile(std::function<bool(char)> predicate) {
    std::string result;
    while (position < input.length() && predicate(input[position])) {
        result += input[position++];
    }
    return result;
}

