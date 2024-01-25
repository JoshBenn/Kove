mod lexer;

fn main() {
    let input = String::new();
    let mut lexer = lexer::Lexer::new(input);
    lexer.tokenize();

    for token in lexer.tokens {
        println!("Token: {}", token);
    }
}
