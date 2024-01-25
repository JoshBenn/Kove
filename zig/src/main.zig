const std = @import("std");

const TokenType = union(enum) {
    IDENTIFIER,           // Variable names, Function names, etc.
    KEYWORD,              // 'var', 'fn', 'if', 'else'
    STRING_LITERAL,       // Strings,
    CHARACTER_LITERAL,    
    INTEGER_LITERAL,      // Numbers
    FLOAT_LITERAL,
    BOOLEAN_LITERAL,
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
    
    TYPE_ANNOTATION,      // 
    REFERENCE,            // 
    OWNERSHIP,            // `:>`  `<:`  `<:>`
    MODIFIER,             //
    ARRAY_LITERAL,        //
    TUPLE_LITERAL,        //
    DECORATOR,            //
    
    EOF,

    ERROR,
    UNKNOWN,              //
};

pub fn main() !void {
    // Prints to stderr (it's a shortcut based on `std.io.getStdErr()`)
    std.debug.print("All your {s} are belong to us.\n", .{"codebase"});

    // stdout is for the actual output of your application, for example if you
    // are implementing gzip, then only the compressed bytes should be sent to
    // stdout, not any debugging messages.
    const stdout_file = std.io.getStdOut().writer();
    var bw = std.io.bufferedWriter(stdout_file);
    const stdout = bw.writer();

    try stdout.print("Run `zig build test` to run the tests.\n", .{});

    try bw.flush(); // don't forget to flush!
}

test "simple test" {
    var list = std.ArrayList(i32).init(std.testing.allocator);
    defer list.deinit(); // try commenting this out and see if zig detects the memory leak!
    try list.append(42);
    try std.testing.expectEqual(@as(i32, 42), list.pop());
}
