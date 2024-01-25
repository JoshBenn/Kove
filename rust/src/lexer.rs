
// TODO: HEX AND BINARY
// FIX STRING TRANSFERRAL
pub enum Token {
    // Literals
    Identifier(String), Keyword(Keyword),            // Special
    String(String), Integer(String), Float(String),  // All else

    // Operators
    Tick, Tilde, Bang, At, Pound, Dollar, Percent, Caret, Ampersand, Star, Minus, 
    Equal, Plus, Backslash, Pipe, Apostrophe, Quote, Dot, Slash, Question, Colon, 
    
    // Special / Mixed
    LeftBracket, RightBracket,

    // Delimiters
    Comma, Semicolon,
    OpenRound, ClosedRound, 
    OpenSquare, ClosedSquare, 
    OpenCurly, ClosedCurly,

    // Documentation / Comments
    Document(String), Comment(String), MultiComment(String),
    
    // End of File
    EndOfFile,

    // Error Expression
    ERROR(String),
}

impl std::fmt::Display for Token {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            // Literals
            Self::Identifier(s)     => write!(f, "IDENTIFIER: {}", s),
            Self::Keyword(s)        => write!(f, "KEYWORD: {}", s),
            Self::String(s)         => write!(f, "STRING_LITERAL: {}", s),
            Self::Integer(s)        => write!(f, "INTEGER_LITERAL: {}", s),
            Self::Float(s)          => write!(f, "FLOAT_LITERAL: {}", s),
            // Operators
            Self::Tick                       => write!(f, "O_TICK"),
            Self::Tilde                      => write!(f, "O_TILDE"),
            Self::Bang                       => write!(f, "O_BANG"),
            Self::At                         => write!(f, "O_AT"),
            Self::Pound                      => write!(f, "O_POUND"),
            Self::Dollar                     => write!(f, "O_DOLLAR"),
            Self::Percent                    => write!(f, "O_PERCENT"),
            Self::Caret                      => write!(f, "O_CARET"),
            Self::Ampersand                  => write!(f, "O_AMPERSAND"),
            Self::Star                       => write!(f, "O_STAR"),
            Self::Minus                      => write!(f, "O_MINUS"),
            Self::Equal                      => write!(f, "O_EQUAL"),
            Self::Plus                       => write!(f, "O_PLUS"),
            Self::Backslash                  => write!(f, "O_BACKSLASH"),
            Self::Pipe                       => write!(f, "O_PIPE"),
            Self::Apostrophe                 => write!(f, "O_APOSTROPHE"),
            Self::Quote                      => write!(f, "O_QUOTE"),
            Self::Dot                        => write!(f, "O_DOT"),
            Self::Slash                      => write!(f, "O_SLASH"),
            Self::Question                   => write!(f, "O_QUESTION"),
            Self::Colon                      => write!(f, "O_COLON"),
            // Special / Mixed
            Self::LeftBracket                => write!(f, "S_LEFT_BRACKET"),
            Self::RightBracket               => write!(f, "S_RIGHT_BRACKET"),
            // Delimiters
            Self::Comma                      => write!(f, "D_COMMA"),
            Self::Semicolon                  => write!(f, "D_COLON"),
            Self::OpenRound                  => write!(f, "D_OPEN_ROUND"),
            Self::ClosedRound                => write!(f, "D_CLOSE_ROUND"),
            Self::OpenSquare                 => write!(f, "D_OPEN_SQUARE"),
            Self::ClosedSquare               => write!(f, "D_CLOSE_SQUARE"),
            Self::OpenCurly                  => write!(f, "D_OPEN_CURLY"),
            Self::ClosedCurly                => write!(f, "D_CLOSE_CURLY"),
            // Documentation / Comments
            Self::Comment(s)        => write!(f, "COMMENT: {}", s),
            Self::Document(s)       => write!(f, "DOCUMENT: {}", s),
            Self::MultiComment(s)   => write!(f, "MULTI_COMMENT: {}", s),
            // End of File
            Self::EndOfFile                  => write!(f, "END_OF_FILE"),
            // Error
            Self::ERROR(s)          => write!(f, "ERROR: {}", s),
        }
    }
}

pub fn match_operator(c: char) -> Token {
    match c {
        // 31 Operators and Delimiters
        '`' => Token::Tick,
        '~' => Token::Tilde,
        '!' => Token::Bang,
        '@' => Token::At,
        '#' => Token::Pound,
        '$' => Token::Dollar,
        '%' => Token::Percent,
        '^' => Token::Caret,
        '&' => Token::Ampersand,
        '*' => Token::Star,
        '(' => Token::OpenRound,
        ')' => Token::ClosedRound,
        '-' => Token::Minus,
        '+' => Token::Plus,
        '=' => Token::Equal,
        '[' => Token::OpenSquare,
        ']' => Token::ClosedSquare,
        '{' => Token::OpenCurly,
        '}' => Token::ClosedCurly,
        '|' => Token::Pipe,
        '\\' => Token::Backslash,
        ';' => Token::Semicolon,
        ':' => Token::Colon,
        '\'' => Token::Apostrophe,
        '"' => Token::Quote,
        ',' => Token::Comma,
        '<' => Token::LeftBracket,
        '>' => Token::RightBracket,
        '.' => Token::Dot,
        '/' => Token::Slash,
        '?' => Token::Question,
        _ => Token::ERROR(String::from(c)),        
    }
}

pub fn is_operator(c: char) -> bool {
    match c {
        // 31 Operators and Delimiters
        | '`' | '~' | '!' | '@' | '#' | '$' | '%' | '^' | '&' | '*' 
        | '(' | ')' | '-' | '+' | '=' | '[' | ']' | '{' | '}' | '|'  
        | ';' | ':' | '"' | ',' | '<' | '>' | '.' | '/' | '?' 
        | '\\'| '\'' 
        => true,
        _ => false,        
    }
}

fn is_whitespace(c: char) -> bool {
    match c {
        | ' '
        | '\r'
        | '\t'
        | '\n'
        // | '\v'                                                -- Unknown Character
        // | '\f'                                                -- Unknown Character
        // | '\u{0009}'  // Character Tabulation                 -- Unreachable Pattern
        // | '\u{000A}'  // Line Feed `\n`                       -- Unreachable Pattern 
        | '\u{000B}'  // Line Tabulation `\v`
        | '\u{000C}'  // Form Feed `\f`
        // | '\u{000D}'  // Carraige Return `\r`                 -- Unreachable Pattern
        // | '\u{0020}'  // Space                                -- Unreachable Pattern
        | '\u{0085}'  // Next Line
        | '\u{00A0}'  // No Break Space (Equivalent to Space)
        | '\u{1680}'  // Ogham Space
        | '\u{2000}'  // En Quad
        | '\u{2001}'  // Em Quad (Mutton Quad)
        | '\u{2002}'  // En Space
        | '\u{2003}'  // Em Space (Mutton)
        | '\u{2004}'  // Three-Per-Em Space (Thick Space)
        | '\u{2005}'  // Four-Per-Em Space (Mid Space)
        | '\u{2006}'  // Six-Per-Em Space
        | '\u{2007}'  // Figure Space
        | '\u{2008}'  // Punctuation Space
        | '\u{2009}'  // Thin Space
        | '\u{200A}'  // Hair Space
        | '\u{2028}'  // Line Separator
        | '\u{2029}'  // Paragraph Separator
        | '\u{202F}'  // Narrow No-Break Space
        | '\u{205F}'  // Medium Mathematical Space (Latex `\:`)
        | '\u{3000}'  // Ideographic Space
          => true,
        _ => false,
    }
}

fn is_alpha(c: char) -> bool {
    match c {
        'a'..='z' | 'A'..='Z' | '_' | '-' => true,
        _ => false
    }
}

fn is_number(c: char) -> bool {
    match c {
        '0'..='9' | '_' => true,
        _ => false,
    }
}

fn is_number_lit(c: char) -> bool {
    match c {
        '0'..='9' | '_' | 'e' | 'E' | '+' | '-' => true,
        _ => false,
    }
}
pub enum Keyword {
    If, Else, While, Break, Continue,
    For, Loop, Match, Switch, Return,

    Sint, I8, I16, I32, I64, I128,
    Uint, U8, U16, U32, U64, U128,
    F32, F64,
    Bool, Str, Vec, Map,
    Struct, Enum, Trait, Axiom,
    Where, True, False,
    Cnst, Stat, Var, Let,
    Pub, Use, SelfRef, 
    Result, Option,
    Fn,
    Async, Await, Virt, Thread,

    Unknown,
}

impl std::fmt::Display for Keyword {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            Keyword::If       => write!(f, "IF"),
            Keyword::Else     => write!(f, "ELSE"),
            Keyword::While    => write!(f, "WHILE"),
            Keyword::Break    => write!(f, "BREAK"),
            Keyword::Continue => write!(f, "CONTINUE"),
            Keyword::For      => write!(f, "FOR"),
            Keyword::Loop     => write!(f, "LOOP"),
            Keyword::Match    => write!(f, "MATCH"),
            Keyword::Switch   => write!(f, "SWITCH"),
            Keyword::Return   => write!(f, "RETURN"),
            Keyword::Sint     => write!(f, "SINT"),
            Keyword::I8       => write!(f, "I8"),
            Keyword::I16      => write!(f, "I16"),
            Keyword::I32      => write!(f, "I32"),
            Keyword::I64      => write!(f, "I64"),
            Keyword::I128     => write!(f, "I128"),
            Keyword::Uint     => write!(f, "UINT"),
            Keyword::U8       => write!(f, "U8"),
            Keyword::U16      => write!(f, "U16"),
            Keyword::U32      => write!(f, "U32"),
            Keyword::U64      => write!(f, "U64"),
            Keyword::U128     => write!(f, "U128"),
            Keyword::F32      => write!(f, "F32"),
            Keyword::F64      => write!(f, "F64"),
            Keyword::Bool     => write!(f, "BOOL"),
            Keyword::Str      => write!(f, "STR"),
            Keyword::Vec      => write!(f, "VEC"),
            Keyword::Map      => write!(f, "MAP"),
            Keyword::Struct   => write!(f, "STRUCT"),
            Keyword::Enum     => write!(f, "ENUM"),
            Keyword::Trait    => write!(f, "TRAIT"),
            Keyword::Axiom    => write!(f, "AXIOM"),
            Keyword::Where    => write!(f, "WHERE"),
            Keyword::True     => write!(f, "TRUE"),
            Keyword::False    => write!(f, "FALSE"),
            Keyword::Cnst     => write!(f, "CNST"),
            Keyword::Stat     => write!(f, "STAT"),
            Keyword::Var      => write!(f, "VAR"),
            Keyword::Let      => write!(f, "LET"),
            Keyword::Pub      => write!(f, "PUB"),
            Keyword::Use      => write!(f, "USE"),
            Keyword::SelfRef  => write!(f, "SELF_REF"),
            Keyword::Result   => write!(f, "RESULT"),
            Keyword::Option   => write!(f, "OPTION"),
            Keyword::Fn       => write!(f, "FN"),
            Keyword::Async    => write!(f, "ASYNC"),
            Keyword::Await    => write!(f, "AWAIT"),
            Keyword::Virt     => write!(f, "VIRT"),
            Keyword::Thread   => write!(f, "THREAD"),
            Keyword::Unknown  => write!(f, "UNKNOWN"),
        }
    }
}

fn is_keyword(word: &str) -> Option<Keyword>  {
    let result = match word {
        "if"       => Keyword::If,
        "else"     => Keyword::Else,
        "while"    => Keyword::While,
        "break"    => Keyword::Break,
        "continue" => Keyword::Continue,
        "for"      => Keyword::For,
        "loop"     => Keyword::Loop,
        "match"    => Keyword::Match,
        "switch"   => Keyword::Switch,
        "return"   => Keyword::Return,
        "sint"     => Keyword::Sint,
        "i8"       => Keyword::I8,
        "i16"      => Keyword::I16,
        "i32"      => Keyword::I32,
        "i64"      => Keyword::I64,
        "i128"     => Keyword::I128,
        "uint"     => Keyword::Uint,
        "u8"       => Keyword::U8,
        "u16"      => Keyword::U16,
        "u32"      => Keyword::U32,
        "u64"      => Keyword::U64,
        "u128"     => Keyword::U128,
        "f32"      => Keyword::F32,
        "f64"      => Keyword::F64,
        "bool"     => Keyword::Bool,
        "str"      => Keyword::Str,
        "vec"      => Keyword::Vec,
        "map"      => Keyword::Map,
        "struct"   => Keyword::Struct,
        "enum"     => Keyword::Enum,
        "trait"    => Keyword::Trait,
        "axiom"    => Keyword::Axiom,
        "where"    => Keyword::Where,
        "true"     => Keyword::True,
        "false"    => Keyword::False,
        "cnst"     => Keyword::Cnst,
        "stat"     => Keyword::Stat,
        "var"      => Keyword::Var,
        "let"      => Keyword::Let,
        "pub"      => Keyword::Pub,
        "use"      => Keyword::Use,
        "self"     => Keyword::SelfRef,
        "Result"   => Keyword::Result,
        "Option"   => Keyword::Option,
        "fn"       => Keyword::Fn,
        "async"    => Keyword::Async,
        "await"    => Keyword::Await,
        "virt"     => Keyword::Virt,
        "thread"   => Keyword::Thread,
        _ => Keyword::Unknown,
    };

    match result {
        Keyword::Unknown => None,
        _ => Some(result),
    }
}

pub struct Lexer {
    pos: usize,
    input: String,
    pub tokens: Vec<Token>,
}

impl Lexer {
    pub fn new(input: String) -> Self {
        Self {
            pos: 0,
            input,
            tokens: vec![],
        }
    }

    pub fn tokenize(&mut self) {
        let input: Vec<char> = self.input.chars().collect();
        let mut has_slash = false;

        while self.pos < self.input.len() {

            if is_whitespace(input[self.pos]) { 
                self.pos += 1;
            }
            // Handle Number, Identifier, or keyword
            else if is_alpha(input[self.pos]) || is_number(input[self.pos]) {
                let mut literal = String::new();
                // Collect all underscores
                while self.pos < input.len() && input[self.pos] == '_' {
                    literal.push(input[self.pos]);
                    self.pos += 1;
                }
                // If the input sequence is an integer or float
                if is_number(input[self.pos]) || input[self.pos] == '.' {
                    let mut has_dot = false;
                    let mut has_exp = false;

                    while self.pos < input.len() && is_number_lit(input[self.pos]) {
                        // Check for dot - deal with multiple dots
                        if input[self.pos] == '.' {
                            if has_dot { 
                                self.tokens.push(Token::ERROR(literal)); 
                                return;
                            } else { has_dot = true; } // Set dot true
                        } 
                        // Check for exponent -- deal with multiple exponents
                        else if input[self.pos] == 'e' || input[self.pos] == 'E' {
                            if has_exp {
                                self.tokens.push(Token::ERROR(literal)); 
                                return;
                            } else { has_exp = true; } // Set exp true
                        }
                        literal.push(input[self.pos]);
                        self.pos += 1;
                    }
                    // Strip '_'
                    literal = literal.replace('_', "");

                    // Append token -- Ensure correct type
                    if has_dot || has_exp {
                        self.tokens.push(Token::Float(literal));  
                    } else {
                        self.tokens.push(Token::Integer(literal));
                    }
                }

                // Handle tokenizing Identifiers and Keywords
                else if is_alpha(input[self.pos]) {
                    while self.pos < input.len() && !is_whitespace(input[self.pos]) {
                        if !is_alpha(input[self.pos]) && !is_number(input[self.pos]) {
                            self.tokens.push(Token::ERROR(literal));
                            return;
                        }
                        literal.push(input[self.pos]);
                        self.pos += 1;
                    }
                    match is_keyword(&literal) {
                        Some(kw) => {
                            self.tokens.push(Token::Keyword(kw));
                        },
                        None => self.tokens.push(Token::Identifier(literal)),
                    }
                }
                continue;
            } // End Numbers, Identifiers, Keywords
            
            // Handle operators and their subsequent characteristics
            else if is_operator(input[self.pos]) {
                let mut literal = String::new();
                // Deal with strings 
                if input[self.pos] == '"' {
                    self.tokens.push(Token::Quote);
                    self.pos += 1;
                    let mut slash_check = false;

                    while self.pos < input.len() && (input[self.pos] != '"' && !slash_check) {
                        if input[self.pos] == '\\' { slash_check = true; }
                        else { slash_check = false; }

                        literal.push(input[self.pos]);
                        self.pos += 1;
                    }
                    // Handle the error
                    if input[self.pos] != '"' {
                        self.tokens.push(Token::ERROR(String::from(input[self.pos])));
                        return;
                    }
                    self.tokens.push(Token::String(literal));
                    continue;
                }

                // Deal with comments
                if has_slash && (input[self.pos] == '/' || input[self.pos] == '*') {
                    if input[self.pos] == '/' {
                        self.tokens.push(Token::Slash);
                        self.pos += 1;

                        // Check for document
                        if self.pos < input.len() && input[self.pos] == '/' {
                            self.tokens.push(Token::Slash);

                            while self.pos < input.len() && input[self.pos] != '\n' {
                                literal.push(input[self.pos]);
                                self.pos += 1;
                            }
                            self.tokens.push(Token::Document(literal));
                        }

                        // Standard comment
                        else {
                            while self.pos < input.len() && input[self.pos] != '\n' {
                                literal.push(input[self.pos]);
                                self.pos += 1;
                            }
                            self.tokens.push(Token::Comment(literal));
                        }
                    } // End Normal Comments and Documents

                    // Multi-line comment
                    else {
                        self.tokens.push(Token::Star);
                        self.pos += 1;

                        while self.pos < input.len() && input[self.pos] != '*' {
                            literal.push(input[self.pos]);
                            self.pos += 1;
                        }
                        self.tokens.push(Token::Star);
                        self.pos += 1;
                        // Send an error if it wasn't finished correctly
                        if input[self.pos] != '/' {
                            self.tokens.push(Token::ERROR(literal));
                            return;
                        }
                        self.tokens.push(Token::MultiComment(literal));
                        self.tokens.push(Token::Slash);
                        self.pos += 1;
                    }
                    continue;
                } // End handling Comments / Documents

                // Manage `/` tracking boolean
                if input[self.pos] == '/' { has_slash = true; } 
                else { has_slash = false; }

                // All operators if not accounted for above
                let operator = match_operator(input[self.pos]);

                // Check for error passed
                match operator {
                    Token::ERROR(e) => {
                        self.tokens.push(Token::ERROR(e));
                        return;
                    },
                    _ => self.tokens.push(operator),
                }
                self.pos += 1;
            }


            // All other cases are errors
            else { 
                self.tokens.push(Token::ERROR(String::from(input[self.pos])));
                return;
            }
        } // End While

        // End of the file
        self.tokens.push(Token::EndOfFile);
    }
}