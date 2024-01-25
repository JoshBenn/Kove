// module;
#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_set>

// export module lexer;

//export enum class TokenType {
enum class TokenType {
    IDENTIFIER,           // Variable names, Function names, etc.
    KEYWORD,              // 'var', 'fn', 'if', 'else'
    STRING_LITERAL,       // Strings,
    CHARACTER_LITERAL,    
    INTEGER_LITERAL,      // Numbers
    FLOAT_LITERAL,
    
    BOOLEAN_LITERAL,
    BOOL_TRUE,
    BOOL_FALSE,

    OPERATOR,             // `+`  `-`  `*`  `/`
    OP_TILDE,
    OP_BANG,
    OP_AT,
    OP_POUND,
    OP_DOLLAR,
    OP_PERCENT,
    OP_CARET,
    OP_AMPERSAND,
    OP_STAR,
    OP_MINUS,
    OP_EQUAL,
    OP_PLUS,
    OP_BACKSLASH,
    OP_PIPE,
    OP_APOSTROPHE,
    OP_QUOTE,
    OP_LESS,
    OP_DOT,
    OP_GREATER,
    OP_SLASH,
    OP_QUESTION,
    OP_COLON,
    
    DELIMITER,            // `,`  `;`  `(`  `)`  `[`  `]`  `{`  `}`
    D_COMMA,
    D_SEMICOL,
    D_OPENROUND,
    D_CLOSEROUND,
    D_OPENSQUARE,
    D_CLOSESQUARE,
    D_OPENCURLY,
    D_CLOSECURLY,
    COMMENT,              // Duh
    DOCUMENT,
    MULTI_COMMENT,
    
    ERROR,
    UNKNOWN,              //
};

//export struct Token {
struct Token {
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value) : type(type), value(std::move(value)) {}
};

//export class Lexer {
class Lexer {
    std::string input;
    std::size_t pos;
    std::vector<Token> tokens;

public:
    explicit Lexer(std::string input) : input(std::move(input)), pos(0) {}
    
    std::vector<Token> tokenize() {
        while (pos < input.size()) {
            if (isWhitespace(input[pos])) {
                pos++;
            }
            else if (is_(input[pos])) {
                if (pos + 1 < input.size()) {
                    if (isDigit(input[pos + 1])) {
                        tokenizeNumber();
                    }
                    else if (isAlpha(input[pos + 1])) {
                        tokenizeIdentifierOrKeyword();
                    }
                }
            }
            else if (isDigit(input[pos])) {
                tokenizeNumber();
            }
            else if (isAlpha(input[pos])) {
                tokenizeIdentifierOrKeyword();
            }
            else if (input[pos] == '.') {
                if (pos + 1 < input.length() && input[pos] != '.') {
                    tokenizeDelimiter();
                } else { tokenizeOperator(); }
            }
            else if (isOperatorChar(input[pos])) {
                tokenizeOperator();
            }
            else if (isDelimiterChar(input[pos])) {
                tokenizeDelimiter();
            }
            else {
                throw std::runtime_error("Could not tokenize character");
            }
        }
        return tokens;
    }

private:
    // ############################# White Space #############################
    // Normal ASCII characters
    bool isWhitespace(char c) {
        switch (c) {
            case  ' ':
            case '\r':
            case '\n':
            case '\t':
                return true;
            default:
                return false;
        }
    }

    // std::string individual characters
    /**
     * <https://en.wikipedia.org/wiki/Template:Whitespace_(Unicode)>
    */ 
    bool isWhitespace(std::string s) {
        return s == " " 
            || s == "\r" 
            || s == "\t" 
            || s == "\n"
            || s == "\v"
            || s == "\f"
            || s == "\u0009"  // Character Tabulation
            || s == "\u000A"  // Line Feed `\n`
            || s == "\u000B"  // Line Tabulation `\v`
            || s == "\u000C"  // Form Feed `\f`
            || s == "\u000D"  // Carraige Return `\r`
            || s == "\u0020"  // Space
            || s == "\u0085"  // Next Line
            || s == "\u00A0"  // No Break Space (Equivalent to Space)
            || s == "\u1680"  // Ogham Space
            || s == "\u2000"  // En Quad
            || s == "\u2001"  // Em Quad (Mutton Quad)
            || s == "\u2002"  // En Space
            || s == "\u2003"  // Em Space (Mutton)
            || s == "\u2004"  // Three-Per-Em Space (Thick Space)
            || s == "\u2005"  // Four-Per-Em Space (Mid Space)
            || s == "\u2006"  // Six-Per-Em Space
            || s == "\u2007"  // Figure Space
            || s == "\u2008"  // Punctuation Space
            || s == "\u2009"  // Thin Space
            || s == "\u200A"  // Hair Space
            || s == "\u2028"  // Line Separator
            || s == "\u2029"  // Paragraph Separator
            || s == "\u202F"  // Narrow No-Break Space
            || s == "\u205F"  // Medium Mathematical Space (Latex `\:`)
            || s == "\u3000"; // Ideographic Space
    }

    // #############################    Digit    #############################
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    // #############################    Alpha    #############################
    bool isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    // #############################      _      #############################
    bool is_(char c) {
        return c == '_';
    }

    // #############################  Operators  #############################
    bool isOperatorChar(char c) {
        switch (c) {
            case '~':
            case '!':
            case '@':
            case '#':
            case '$':
            case '%':
            case '^':
            case '&':
            case '*':
            case '-':
            case '=':
            case '+':
            case '\\':
            case '|':
            case '\'':
            case '"':
            case '<':
            case '.': // Shared Delim
            case '>':
            case '/':
            case '?':
            case ':': // Shared Delim
                return true;
            default:
                return false;
        }
    }

    bool isOperator(std::string &value) {
        std::unordered_set<std::string> operators = {
            // Single-character operators
            "~", "`", "!", "@", "#", "$", "%", "^", "&", "*", "-", "_", "+",
            "=", "|", "\\", ":", ";", "'", "\"", "<", ",", ">", ".", "/", "?",

            // Multi-character logical operators
            "&&", "||", "|:|", "==", "<=", ">=", "!=", "?=",

            // Ownership and directional operators
            ":>", "<:", "<:>", "&", ":=", "*",

            // Bitwise and other operations
            "<<", ">>", "<<=", ">>=", "...", "=..", "..=", "=.=", "::", "->", "=>",

            // Mathematical operations
            "++", "--", "+=", "-=", "/=", "*=", "^=",
        };
        return operators.find(value) != operators.end();
    }

    bool isDelimiterChar(char c) {
        switch(c) {
            case '{':
            case '}':
            case '(':
            case ')':
            case '[':
            case ']':
            case ';':
            case ',':
//            case ':':
            case '.':
                return true;
            default:
                return false;
        }
    }

    bool isKeyword(const std::string &value) {
        static const std::unordered_set<std::string> keywords = {
            /*Control Flow      */  
            "if", "else", "while", "for", "break", "continue", "switch", "case", "default", "return", "match",
            "loop",
            /*Data Types        */  
            "int", "i8", "i16", "i32", "i64", "i128", "uint", "u8", "u16", "u32", "u64", "u128", "f32", "f64",
            "bool", "str", "vec", "struct", "enum", "trait",
            /*Variable Modifiers*/  
            "cnst", "stat", "var", "let",
            /*Access Specifiers */  
            "pub", "use", "self",
            /*Error Handling    */  
            "Result", "Option", 
            /*Function          */  
            "fn", "pure",
            /*Featureset        */  
            "async", "await", "virt", "thread", 
            /*Generics          */  
            "where",
        };
        return keywords.find(value) != keywords.end();
    }

    void tokenizeIdentifierOrKeyword() {
        size_t start = pos;

        while (pos < input.length() && (isAlpha(input[pos]) || is_(input[pos]) || isDigit(input[pos]))) {
            pos++;
        }
        std::string value = input.substr(start, pos - start);

        TokenType type = isKeyword(value)? TokenType::KEYWORD : TokenType::IDENTIFIER;
        tokens.push_back(Token(type, value));
    }



    void tokenizeNumber() {
        size_t start = pos;
        bool has_decimal = false, has_exponent = false;

        while (pos < input.length() 
                && (isDigit(input[pos]) || is_(input[pos]) || input[pos] == 'e' || input[pos] == 'E' 
                || (has_exponent && (input[pos] == '+' || input[pos] == '-')))) {
            // Check for decimal and exponent
            if (input[pos] == '.') {
                if (has_decimal) { break; }  // Only one decimal point allowed
                has_decimal = true;
            } else if (input[pos] == 'e' || input[pos] == 'E') {
                if (has_exponent) { break; } // Only one exponent allowed
                has_exponent = true;
            }
            pos++;
        }
        std::string value = input.substr(start, pos - start);
        value.erase(std::remove(value.begin(), value.end(), '_'), value.end());

        TokenType type = (has_decimal || has_exponent)? TokenType::FLOAT_LITERAL : TokenType::INTEGER_LITERAL;
        tokens.push_back(Token(type, value));
    }

    void tokenizeString() {
        size_t start = pos++;

        while (pos < input.length() && input[pos] != '"') {
            if (input[pos] == '\\' && pos + 1 < input.length()) {
                pos++;
            }
            pos++;
        }

        if (pos >= input.length()) {
            throw std::runtime_error("Unterminated string");
        }

        std::string value = input.substr(start + 1, pos - start - 1);
        pos++;
        tokens.push_back(Token(TokenType::STRING_LITERAL, value));
    }

    void tokenizeOperator() {  
        // Handle :      
        if (pos + 1 < input.length() && input[pos] == ':'
            && !(input[pos + 1] == '>' || input[pos + 1] == ':' || input[pos + 1] == '=')) {
            tokens.push_back(Token(TokenType::OPERATOR, ":"));
            pos++;
            return;
        }
        // Handle Comments
        if (pos + 1 < input.length() && input[pos] == '/' && ((input[pos + 1] == '/' || input[pos + 1] == '*') )) {
            if (input[pos + 1] == '/') {
                if (pos + 2 < input.length() && input[pos + 2] == '/') {
                    tokens.push_back(Token(TokenType::DOCUMENT, "///"));
                    pos += 3;
                    tokenizeComment();
                    return;
                }
                tokens.push_back(Token(TokenType::COMMENT, "//"));
                pos += 2;
                tokenizeComment();
                return;
            }
            if (input[pos + 1 == '*']) {
                tokens.push_back(Token(TokenType::MULTI_COMMENT, "/*"));
                pos += 2;
                tokenizeComment();
                if (!(pos + 1 < input.length() && input[pos] == '*' && input[pos + 1] == '/')) {
                    throw std::runtime_error("Incorrect Comment Delineation");
                }
                tokens.push_back(Token(TokenType::MULTI_COMMENT, "*/"));
                pos += 2;
                return;
            }
        }
        // Handle strings
        if (input[pos] == '"') {
            tokens.push_back(Token(TokenType::OPERATOR, "\""));
            tokenizeString();
            tokens.push_back(Token(TokenType::OPERATOR, "\""));
            return;
        }
        size_t start = pos++;
        
        while (pos < input.length() && isOperatorChar(input[pos]) && !isWhitespace(input[pos])) {
            pos++;
        }
        std::string value = input.substr(start, pos - start);
        if (!isOperator(value)) {
            throw std::runtime_error("Incorrect Operator Sequence");
        }
        tokens.push_back(Token(TokenType::OPERATOR, value));
    }

    void tokenizeComment() {
        size_t start = pos;

        while (pos < input.length() && input[pos] != '*') {
            if (input[pos] == '\\' && pos + 1 < input.length()) {
                pos++;
            }
            pos++;
        }

        std::string value = input.substr(start, pos - start);
        tokens.push_back(Token(TokenType::STRING_LITERAL, value));
    }

    void tokenizeDelimiter() {
        std::string value = input.substr(pos++, 1);

        tokens.push_back(Token(TokenType::DELIMITER, value));
    }
};