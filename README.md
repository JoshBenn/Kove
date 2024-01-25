# Kove

## Syntax Overview: 
KEYWORD:
- Declaration: 
   - Control Flow
    | `if`     | `else` | `while` | `break` | `continue`
    | `for`    | `loop` | `match` | `switch`| `return`
   - Data Types
    | `int`    | `i8`   | `i16`   | `i32`   | `i64` | `i128` 
    | `uint`   | `u8`   | `u16`   | `u32`   | `u64` | `u128` 
    | `f32`    | `f64`
    | `bool`   | `str`  | `vec" ` | `map`
    | `struct` | `enum` | `trait` | `axiom`
   - Comparison
    | `where`  | `true` | `false`
   - Variable Declaration
    | `cnst`   | `stat` | `var`   | `let`
   - Access Specifiers
    | `pub`    | `use`  | `self` 
   - Error Handling
    | `Result` | `option`
   - Function
    | `fn`     | `pure`
   - Features
    | `async`  | `await` | `virt` | `thread`

IDENTIFIER:
- [`_`][`a`-`z`][`A`-`Z`][`_`][`0`-`9`][`-`]
  - Must be non-empty, must start with `_` or unicode character
  - <https://www.unicode.org/reports/tr31/tr31-37.html>

LITERAL:
- Char `''`, String `""`, Raw String `#""#`, Byte `b''`, Byte String `b""`, Raw Byte String `b#""#`
- Escapes: 
  - Ascii: [`\x41`][`\n`][`\r`][`\t`][`\\`][`\0`]
  - Byte: [`\x7F`][`\n`][`\r`][`\t`][`\\`][`\0`]
  - Unicode: [`\u{7FFF}`]
  - Quote [`\'`][`\"`]
- Numbers: --Allow `_` as a visual separator for number literals--
  - Decimal: [`0`-`9`]
  - Hex: `0x`[`0`-`9`][`a`-`f`][`A`-`F`]
  - Binary: `0b`[`0`-`1`]
  - Floating: [`0`-`9`][`.`][`0`-`9`][`e`][`E`][`+``-`][`0`-`9`]
- Index:
  - Tuples, Arrays, Lists, or Vectors can be indexed with `[` `0`-`9` `]` or `.`[`0`-`9`]
- Suffixes: -- `IDENTIFIER` followed by `:` or before `=`
  - Number: `int`, `i8`, `i16`, `i32`, `i64`, `i128`, `uint`, `u8`, `u16`, `u32`, `u64`, `u128`, `f32`, `f64`
  - Array: `[` T `]`
  - String: `str`
  - Vector: `vec<T>`

OPERATOR:
Base:
- Tilde: `~`, Tick, Bang: `!`, At: `@`, Hash: `#`, Dollar: `$`, Percent: `%`
- Carrot: `^`, Ampersand: `&`, Star: `*`, Minus: `-`, Underscore: `_`, Plus: `+`
- Equal: `=`, Pipe: `|`, Back: `\`, Colon: `:`, SemiColon: `;`, Apostrophe: `'`
- Quote: `"`, Left: `<`, Comma: `,`, Right: `>`, Dot: `.`, Forward: `/`, Question: `?`
Uses:
- Assignment:
    - Standard:
        - Simple `=`, Deref `:=`, Axiom `:-`, Add `+=`, Sub `-=`, Mult `*=`, Div `/=`, Mod `%=`, LeftShift `<<`, RightShift `>>`
    - Bitwise:
        - ..Standard, AND `&=`, OR `|=`, XOR `^=`, LeftShift `<<=`, RightShift `>>=`
- Logical:
    - Standard:
        - NOT `!`, AND `&&`, OR `||`, XOR `|!|`
    - Bitwise:
        - NOT `~`, AND `&`, OR `|`, XOR `^`
    - Comparison (Both):
        - EQUAL `==`, LEQ `<=`, GEQ `>=`, NOTEQ `!=`, Greater `>`, Less `<`, MatchType `?=`
- Clojure: `|` `LITERAL`  `|`
- Ownership
    - Variable:
        - Transfer Ownership `<:`, Swap Ownership `<:>`, Reference `&`
    - Function:
        - Parameter Requiring Ownership `:>`, Referencing `&` (Primarily used for mutating internal values)
- Operations:
  - Iterator
    - (x to y) `...`, [x to y) `=..`, (x to y] `..=`, [x to y] `=.=`
  - Path: `::`
  - Type Conversion / Output: `->`
  - Relationship / "Therefore": `=>`
  - Mathematical:
    - ADD `+`, SUB `-`, Increment `++`, Decrement `--`, 
    - Divide `/`, Multiply `*`, Power `**`, Modulus `%`, 
  - Access Attributes: `.`
  - Index: `[` `uint` `]`
  - Separate Fields: `,`
  - Type Identifier `:`
- Macro: `#[` `IDENTIFIER` `]`
- Ternary: `condition` `=>` `{`truthy`}``,` `{`falsy`};`
- Unused: `@`, `$`

DELIMITER:
- `[` `]`, `{` `}`, `(` `)`, `<`, `>`

SPECIAL:
- `<`, `>`

RESERVED:
- Prefix: [b]`#`, Suffix: `#`, All KEYWORD, 




## Variables
```
// `var` is a mutable variable
var variable_name: type = expression; // Use `:` to 
var variable_name = expression;

// `let` is an immutable variable
let variable_name: type = expression; // Use `:` to explicate type
let variable_name = expression;

// stat is a static variable -- same location in memory -- mutable
stat var variable_name: type = expression;

// cnst is a constant variable -- 
cnst let variable_name: type = expression;
```




```
// Iterate through a loop within a range from i = 0 to x (non-inclusive)
// cnst or var declaration is necessary
for cnst i := 0=..x { }
(0=..x).iter().for(|cnst i|    );
(0=..x).iter(:>).for(|cnst i|    ); // iter_into() equivalent
(0=..x).iter().for_n(3, |var i|    ); // for every n (3 chosen)


print();
println();
printf();

```


## Functional
- First Class Functions
- Anonymous Functions (Lambdas)
- Iterators
- `map()`, `filter()`,
- Configurable Closures (move & borrow)
- Dataclasses
- Lazy Evaluation
- Tail call recursion
- Pure Function `pure fn`

## Baseline
- CoW as default
    - Issues
        - Thread Safety - concurrent copies of data for modification





```
var count: int = 10;
var name = "Kove";

let pi: float = 3.14;
let greeting = "Hello, World!";

stat var globalCounter: int = 100;

cnst let MAX_SIZE: int = 50;

var x: int = 10;
if x > 5 {
    println("x is greater than 5");
} else {
    println("x is not greater than 5");
}

var i: int = 0;
while i < 10 {
    println(i);
    i += 1;
}

for cnst i := 0=..10 {
    println(i);
}

fn add(a: int, b: int) -> int {
    return a + b;
}

fn add(a: int, b: int) -> int {
    return a + b;
}

dataclass Point {
    var x: int;
    var y: int;
}

let p = Point{ x: 10, y: 20 };
println("Point coordinates: ({}, {})", p.x, p.y);


let numbers = vec![1, 2, 3, 4, 5];
let squares = numbers.iter().map(|n| n * n);
for cnst sq in squares {
    println(sq);
}

let multiply = |a: int, b: int| -> int { a * b };
println("Product: {}", multiply(6, 7));

pure fn factorial(n: int) -> int {
    if n <= 1 { 
        return 1; 
    } else { 
        return n * factorial(n - 1); 
    }
}
println("Factorial of 5: {}", factorial(5));

let lazySeq = (0=..).iter().map(|n| n * n);
for cnst num in lazySeq.take(10) {
    println(num); // prints first 10 square numbers
}

// Assuming thread support in Kove
fn modifyVector(v: vec<int>) {
    for cnst i := 0=..v.len() {
        v[i] += 1; // CoW ensures thread safety during modification
    }
}

let numbers = vec![1, 2, 3];
thread::spawn(|| modifyVector(numbers));
```



KEYWORD:
- Declaration: 
   - Control Flow
    | `if`     | `else` | `while` | `break` | `continue`
    | `for`    | `loop` | `match` | `switch`| `return`
   - Data Types
    | `int`    | `i8`   | `i16`   | `i32`   | `i64` | `i128` 
    | `uint`   | `u8`   | `u16`   | `u32`   | `u64` | `u128` 
    | `f32`    | `f64`
    | `bool`   | `str`  | `vec" ` | `map`
    | `struct` | `enum` | `trait` | `axiom`
   - Comparison
    | `where`  | `true` | `false`
   - Variable Declaration
    | `cnst`   | `stat` | `var`   | `let`
   - Access Specifiers
    | `pub`    | `use`  | `self` 
   - Error Handling
    | `Result` | `option`
   - Function
    | `fn`     | `pure`
   - Features
    | `async`  | `await` | `virt` | `thread`

IDENTIFIER:
- [`_`][`a`-`z`][`A`-`Z`][`_`][`0`-`9`][`-`]
  - Must be non-empty, must start with `_` or unicode character
  - <https://www.unicode.org/reports/tr31/tr31-37.html>

LITERAL:
- Char `''`, String `""`, Raw String `#""#`, Byte `b''`, Byte String `b""`, Raw Byte String `b#""#`
- Escapes: 
  - Ascii: [`\x41`][`\n`][`\r`][`\t`][`\\`][`\0`]
  - Byte: [`\x7F`][`\n`][`\r`][`\t`][`\\`][`\0`]
  - Unicode: [`\u{7FFF}`]
  - Quote [`\'`][`\"`]
- Numbers: --Allow `_` as a visual separator for number literals--
  - Decimal: [`0`-`9`]
  - Hex: `0x`[`0`-`9`][`a`-`f`][`A`-`F`]
  - Binary: `0b`[`0`-`1`]
  - Floating: [`0`-`9`][`.`][`0`-`9`][`e`][`E`][`+``-`][`0`-`9`]
- Index:
  - Tuples, Arrays, Lists, or Vectors can be indexed with `[` `0`-`9` `]` or `.`[`0`-`9`]
- Suffixes: -- `IDENTIFIER` followed by `:` or before `=`
  - Number: `int`, `i8`, `i16`, `i32`, `i64`, `i128`, `uint`, `u8`, `u16`, `u32`, `u64`, `u128`, `f32`, `f64`
  - Array: `[` T `]`
  - String: `str`
  - Vector: `vec<T>`

OPERATOR:
Base:
- Tilde: `~`, Tick, Bang: `!`, At: `@`, Hash: `#`, Dollar: `$`, Percent: `%`
- Carrot: `^`, Ampersand: `&`, Star: `*`, Minus: `-`, Underscore: `_`, Plus: `+`
- Equal: `=`, Pipe: `|`, Back: `\`, Colon: `:`, SemiColon: `;`, Apostrophe: `'`
- Quote: `"`, Left: `<`, Comma: `,`, Right: `>`, Dot: `.`, Forward: `/`, Question: `?`
Uses:
- Assignment:
    - Standard:
        - Simple `=`, Deref `:=`, Axiom `:-`, Add `+=`, Sub `-=`, Mult `*=`, Div `/=`, Mod `%=`, LeftShift `<<`, RightShift `>>`
    - Bitwise:
        - ..Standard, AND `&=`, OR `|=`, XOR `^=`, LeftShift `<<=`, RightShift `>>=`
- Logical:
    - Standard:
        - NOT `!`, AND `&&`, OR `||`, XOR `|!|`
    - Bitwise:
        - NOT `~`, AND `&`, OR `|`, XOR `^`
    - Comparison (Both):
        - EQUAL `==`, LEQ `<=`, GEQ `>=`, NOTEQ `!=`, Greater `>`, Less `<`, MatchType `?=`
- Clojure: `|` `LITERAL`  `|`
- Ownership
    - Variable:
        - Transfer Ownership `<:`, Swap Ownership `<:>`, Reference `&`
    - Function:
        - Parameter Requiring Ownership `:>`, Referencing `&` (Primarily used for mutating internal values)
- Operations:
  - Iterator
    - (x to y) `...`, [x to y) `=..`, (x to y] `..=`, [x to y] `=.=`
  - Path: `::`
  - Type Conversion / Output: `->`
  - Relationship / "Therefore": `=>`
  - Mathematical:
    - ADD `+`, SUB `-`, Increment `++`, Decrement `--`, 
    - Divide `/`, Multiply `*`, Power `**`, Modulus `%`, 
  - Access Attributes: `.`
  - Index: `[` `uint` `]`
  - Separate Fields: `,`
  - Type Identifier `:`
- Macro: `#[` `IDENTIFIER` `]`
- Ternary: `condition` `=>` `{`truthy`}``,` `{`falsy`};`
- Unused: `@`, `$`

DELIMITER:
- `[` `]`, `{` `}`, `(` `)`, `<`, `>`

SPECIAL:
- `<`, `>`

RESERVED:
- Prefix: [b]`#`, Suffix: `#`, All KEYWORD, 






```
axiom Status {
    adult(age) :- age >= 18,           // Can define a relation globally
    child :- !adult,                   // Not exactly sure how this syntax should work
    father :- male && parent,
    mother :- female && parent,
    male |!| female,                   // Exclusive Or - Must declare one or the other
    parent(p),
}

struct Person {
    name: str,
    age: u32,

    trait {
        Status {
            parent(None),   // Must specify passed values -- age is a property so don't have to specify that one and can be done automatically
            male,
            ...             // Syntax pulls in the rest
        }
        Living :- true,     // Can define their own
        std::map::hash,     // Can import external traits
        std::fs::serialize,
    }

    fn new(name: str, age: u32) -> Self {
        return Person { name, age };  // You can also just Person... with no semicolon as a return, but I find this more explicit
    }
    
    // A simple method to display information
    fn display(self) {          // CoW by default
        println("Name: {}, Age: {}", self.name, self.age);
    }
}

// Can add functions to an internal struct
fn Person::increase_age(&self) { // &self passes a modifiable reference, :> if passing ownership
    self.age := self.age + 1; // := is the dereference -- syntacticly explicit
}

// Pure functions - scope is contained entirely within the function
// This is a bad example as this can be either, but ultimately it introduces a "restriction" on the function
// where the function cannot create or modify variables
#[trait(Pure)]
fn greet(person: Person) {
    printf("Hello, %s!\n", person.name); // Printf supported
}

// Main function
fn main() {
    // Creating a new `Person`, `var` for mutable, `let` for immutable
    var person = Person::new("Alice", 30);
    person.increase_age();

    // Using methods of `Person`
    person.display();
    if person.adult {
        println!("{} is an adult.", person.name);
    }

    // Calling a standalone function -- CoW by default
    greet(person);

    // Variables and assignments
    var mut counter = 0;
    counter++;
    println("Counter value: {}", counter);
}

```

