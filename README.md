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
    | `fn`     
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
var variable_name: type = expression; // Use `:` to explicate
var variable_name = expression;

// `let` is an immutable variable
let variable_name = expression;

// stat is a mutable static variable -- same location in memory -- mutable
stat variable_name = expression;

// cnst is an immutable variable -- similar to stat
cnst variable_name = expression;
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



## Examples
### Variable Declaration

```
var count: sint = 10;             // Mutable signed integer
var name = "Kove";                // Mutable string

let pi: f32 = 3.14;               // Immutable 32-bit float
cnst greeting = "Hello, World!";  // Immutable statically available string

stat GLOBAL_COUNTER: sint = 100;  // Mutable statically available signed int

cnst MAX_SIZE: uint = 50;         // Immutable statically available unsigned int
```

### Control Flow
```
var x: sint = 10;

for cnst i : 0=..10 -> sint {          // From i in 0 (inclusive) to 10 (exclusive) converted from uint to sint
    x += i % 2 == 0 => {i}, {0};  // Ternaries supported
}

if x > 5 {
    // Use `{}` to capture a variable and `:` to modify how it's represented
    println("x: {:5}, is more than 5", x);      // 10.00000
} else {
    // Can pass the variable directly
    println("x: {x:1}, is not greater than 5"); // 10.0
}

var i: uint = 0;
while i < 10 {
    print(i++);                        // `print()` Doesn't create a new line
}

var vector: vec<sint> = {0, 1, 2, 3, 4};
for var i := vector.iter() {           // Use `var` for mutable and `:=` to dereference the item
    i *= i;
}
```

### Functions

```
#[trait(pure)]                         // The `pure` trait restricts what is allowed in the function
fn add(a: sint, b: sint) -> sint {     // -- No variable creation or side-effects allowed
    return a + b;                      // -- Visibility of scope is confined to the function itself
}

fn modify(a: &sint, b:> sint) -> uint { // & provides a reference to the actual variable, `:>` demands ownership of the variable
    a := 3;                             // `:=` to dereference and change the variable (made explicit on purpose)
    b *= b;                             // The function owns `b`, so dereferencing is not necessary
    return std::math::abs(a * b);       // The function does not own `a`, so it will be cloned at this point, but `b` will be passed on
}

fn main() {                            // By default, all functions are `void` or `()` and are coerced, `->`, to their output value
    let x: sint = 5;
    let y = 1;
    var z = add(x, y);                 // CoW by default
    let q = modify(&x, <:y);           // Explicit syntactic semantics required for memory safety and visibility of actions
}
```

### Entities and Dataclasses
```
cnst PI: f32 = 3.14159;                    // Declaring a locally global immutable value

enum Colors {
    Blue = 32,
    Green = 42,
    Red = 52,
    Hex(str),
    RGB(u8, u8, u8);

    trait { std::fmt::Display :- fmt(self); }

    fn convert_to_rgb(self) -> Result<self::RGB, Error> {
        if self ?= Colors::Hex && s[0] != '#' { return Error("Not a valid conversion"); }
        let (r_str, g_str, b_str) = (s[1=.=2], s[2..=4], s[4=..(s.size())]);

        // Because converting from a string to a u8 might result in errors
        let r = r_str -> u8 == Ok(v) => { v }, { return Error("Could not convert") };
        let g = g_str -> u8 == Ok(v) => { v }, { return Error("Could not convert") };
        let b = b_str -> u8 == Ok(v) => { v }, { return Error("Could not convert") };

        return self::RGB(r, g, b);
    }

    fn fmt(self) -> std::fmt::Result {
        match self {                   // Maybe implicit returns?
            self::Hex(s) => s,
            self::RGB(r, g, b) => (r, g, b) -> str,
            _ => s -> str, 
        }
    }
}

trait Graphable {                          // Declare axioms which are rulesets and traits
    Valid;                                 // Requires the user to define it
    Visible(distance_from_center) :-       // Can define passed values
        distance_from_center <= 10;
    Type(t) :-
        Cartesian |!| Polar;               // Can implement exclusivit
    AllowedColors(list) :-
        Colors::Blue, Colors::Green;       // Lists separated by a comma
    Convert :- {                           // Tricky one: -> outputs values
        self::Type::Polar(self::Type::Cartesian) -> (r: f32, theta: f32), // Read as "To polar from cartesian"
        self::Type::Cartesian(self::Type::Polar) -> (x: f32, y: f32),     // From Polar to Cartesian
    };
}

struct Cartesian {                         // The usual suspects
    x: f32;
    y: f32;

    trait {                                // Declare which traits to implement
        Graphable {
            Valid :-
                x (<= 100 && >= -100) && y (<= 100 && >= -100);
            Visible( std::math::sqrt(x*x + y*y) );
            Type(Cartesian);
            AllowedColors(Blue);
            Convert :- {
                Polar {
                    let r = std::math::sqrt(x*x + y*y);
                    let theta =  x > 0 => { 
                        std::math::atan(y / x) 
                    }, { 
                        std::math::atan(x / y) + PI 
                    };
                    (r, theta)
                },
                self(x, y) {
                    self.x = x;
                    self.y = y;
                },
            };
        },
    };

    fn new(x: f32, y: f32) -> self {
        return Cartesian {
            x, y,
        };
    }
}

struct Polar {
    r: f32;
    theta: f32;

    trait {                                // Declare which traits to implement
        Graphable {
            Valid :- r <= 3;
            Visible(Graphable::Valid);     // Using the Valid trait within Graphable as the passed truthy value
            Type(Polar);
            AllowedColors(Blue, Green);
            Convert :- {
                Cartesian {
                    let degrees = theta * (180 / PI);
                    let x;
                    let y;
                    if r < 0 {
                        x = 0;
                        y = 0;
                    } else {
                        x = std::math::cos(degrees) / r;
                        y = std::math::sin(degrees) / r;
                    }
                    (x, y)
                },
                self {
                    .r = r;
                    .theta = theta;
                },
            };
        },
    };

    fn new(r: f32, theta: f32) -> self {
        return self { r, theta };                  // I prefer explicit returns for functions as it's easier to read
    }
}


fn main() {
    let p = Point::new(10, 20);
    println("Point coordinates: x: {}, y: {}", p.x, p.y);
    
    let (r, theta) = p.convert();
    println("Polar coordinates: r: {r:3}, theta: {theta:3})
}
```

## TEMPORARY
```
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

fn modifyVector(v: vec<sint>) {
    for cnst i := 0=..v.len() {
        v[i] += 1; // CoW ensures thread safety during modification
    }
}
```



### Other Examples
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

