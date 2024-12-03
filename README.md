# Cf (C-french) Compiler

This is Cf, an in-progress compiler that forms a minimal programming language meant to be written in French and with C-like syntax. In the future, the intention is to integrate some nicer, Python-like features. The compiler generates x86_64 assembly code for macOS.

## Language Features

Cf currently supports:

- Basic arithmetic operations (+, -, \*, /)
- Comparison operations (==, !=, <, <=, >, >=)
- Integer literals
- Expression grouping with parentheses
- Variable declarations and assignments with `soit` (roughly semantically equivalent to `let`)
- Control flow for if-else statements with `si` and `sinon` (semantically equivalent to `if` and `else`)
- Return statements with `retourner` (equivalent to `return`)
- Variable references in expressions
- Scoping with `{` and `}`
- Error handling:
  - Syntax error detection with line and column numbers
  - Variable redeclaration checks
  - Undefined variable usage detection
  - Missing semicolon detection
  - Invalid operator usage detection
  - Stack overflow protection for complex expressions

### Syntax

- Variables are declared using the `soit` keyword
- Return statements use the `retourner` keyword
- If-else statements use the `si` and `sinon` keywords
- Statements must end with semicolons
- Expressions follow standard operator precedence rules

### Operator Precedence (highest to lowest)

1. Parentheses `()`
2. Multiplication and division `*`, `/`
3. Addition and subtraction `+`, `-`
4. Comparison operators `==`, `!=`, `<`, `<=`, `>`, `>=`

## Examples

### Basic Arithmetic

```Cf
retourner (((6 + 6) / 2) * 3) / 9 - 2; // returns 0
```

This example demonstrates nested arithmetic expressions and operator precedence.

### Variable Declaration

```Cf
soit x1 = 4;
soit y1 = 8;
soit x2 = 7;
soit y2 = 11;
soit dx = x2 - x1;
soit dy = y2 - y1;
soit distanceCarre = dx * dx + dy * dy;
retourner distanceCarre;
```

This example calculates the squared distance between two points.

### Comparison Operations

```Cf
soit valeur1 = 2;
soit valeur2 = 3;

soit resultatSuperieurOuEgal1 = valeur1*4 >= valeur2;
soit resultatSuperieurOuEgal2 = valeur1*3 >= valeur2*2;
soit resultatInferieurOuEgal1 = valeur1 <= valeur2;
soit resultatInferieurOuEgal2 = valeur1*3 <= valeur2*2;
soit resultatEgal1 = valeur1*3 == valeur2*2;
soit resultatEgal2 = valeur1 == valeur2;
soit resultatDifferent1 = valeur1 != valeur2;
soit resultatDifferent2 = valeur1*3 != valeur2*2;
soit resultatSuperieur1 = valeur1*4 > valeur2;
soit resultatSuperieur2 = valeur1*3 > valeur2*2;
soit resultatInferieur1 = valeur1 < valeur2;
soit resultatInferieur2 = valeur1*3 < valeur2*2;

retourner   resultatSuperieurOuEgal1 + resultatSuperieurOuEgal2 +
            resultatInferieurOuEgal1 + resultatInferieurOuEgal2 +
            resultatEgal1 + resultatEgal2 + resultatDifferent1 + resultatDifferent2 +
            resultatSuperieur1 + resultatSuperieur2 +
            resultatInferieur1 + resultatInferieur2; // expected return value of 8
```

This example demonstrates all comparison operators.

### Simple Control Flow

```Cf
soit x = 2;
si (x < 3) {
    retourner 1;
} sinon {
    retourner 0;
}
```

This example demonstrates simple control flow with a si-sinon statement.

### Complex Nested Control Flow

```Cf
soit valeur1 = 7;
soit valeur2 = 9;
soit valeur3 = 15;

si (valeur1 + valeur2 < valeur3) {
    si (valeur1 - valeur2 > 0) {
        retourner (valeur3 - valeur1) + valeur2;
    } sinon {
        retourner valeur2 + valeur3;
    }
} sinon {
    si (valeur1 + valeur3 > valeur2 * 4) {
        retourner (valeur1 + valeur2) + valeur3;
    } sinon {
        si (valeur3 + 1 == valeur1 + valeur2) {
            si (valeur2 - valeur1 - 2 >= 0) {
                retourner ((valeur1 * valeur2) + valeur3) / 2; // expected to return 39
            } sinon {
                retourner (valeur1 + valeur3) + valeur2;
            }
        } sinon {
            retourner (valeur1 + valeur2 + valeur3) * 2 - 4;
        }
    }
}
```

This example demonstrates a more complex control flow with nested si-sinon statements.

### Reference Files

At the first level of the repository there are a collection of `asm` and `.cf` files, respectively `tests1-5.asm` and `v1-5CfSample.cf` which contain both Cf code snippets and their associated compiled assembly files.

## Building and Running

### Prerequisites

- GCC/Clang: Apple Clang version 16.0.0
- NASM: >= 2.16.03
- Make: GNU Make 3.81
- macOS

### Building the Compiler

```bash
make
```

### Compiling a Cf Program

```bash
./cf input.cf test5.asm
```

This will generate an assembly file named `test5.asm`.

### Running a Complete Build Pipeline

```bash
make full CF_FILE=yourInput.cf ASM_FILE=yourPreferredOutputFileName.asm
```

or just

```bash
make full
```

to run with default targets defined in Makefile.

This will:

1. Compile your Cf program to assembly
2. Assemble it to an object file
3. Link it into an executable
4. Run the executable and display its return value

### Cleaning Build Files

```bash
make clean
```

## Implementation Details

The compiler follows a traditional compilation pipeline:

1. Lexical analysis (tokenizer)
2. Parsing (recursive descent parser)
3. AST generation
4. Code generation (x86_64 assembly)

## Grammar

<!-- $$
\begin{align*}
  \text{program} &\to \text{statement}* \text{ EOF} \\
\text{statement} &\to \text{return} \;|\; \text{varDecl} \;|\; \text{ifStmt} \;|\; \text{expr} \\
  \text{return} &\to [retourner]\text{ expr [;]} \\
  \text{varDecl} &\to [soit]\text{ identifier [=] expr [;]} \\
\text{ifStmt} &\to [si][(]\text{expr}[)][\text{\{}]\text{statement}*[\text{\}}]([sinon][\text{\{}]\text{statement}*[\text{\}}])?\\
  \text{expr} &\to \text{arithmetic}\ ((\text{==}|\text{!=}|< |\leq |> |\geq )\text{ arithmetic})* \\
 \text{arithmetic} &\to \text{term}\ (([+]|[-])\text{ term})* \\
  \text{term} &\to \text{factor}\ (([*]|[/])\text{ factor})* \\
  \text{factor} &\to [(]\text{ expr }[)] \;|\; \text{primary} \\
  \text{primary} &\to \text{number} \;|\; \text{identifier}\\
\text{identifier} &\to \text{letter}\ (([\text{letter}]|[\text{digit}])* \\
\text{number} &\to \text{digit} \\
\text{letter} &\to \text{[a-zA-Z]} \\
\text{digit} &\to \text{[0-9]}
\end{align*}
$$ -->

![grammar_latex_cogs](https://latex.codecogs.com/png.image?%5Cinline%20%5Clarge%20%5Cdpi%7B150%7D%5Cbg%7Bblack%7D$$%5Cbegin%7Balign*%7D%5Ctext%7Bprogram%7D&%5Cto%5Ctext%7Bstatement%7D*%5Ctext%7BEOF%7D%5C%5C%5Ctext%7Bstatement%7D&%5Cto%5Ctext%7Breturn%7D%5C;%7C%5C;%5Ctext%7BvarDecl%7D%5C;%7C%5C;%5Ctext%7BifStmt%7D%5C;%7C%5C;%5Ctext%7Bexpr%7D%5C%5C%5Ctext%7Breturn%7D&%5Cto%5Bretourner%5D%5Ctext%7Bexpr%5B;%5D%7D%5C%5C%5Ctext%7BvarDecl%7D&%5Cto%5Bsoit%5D%5Ctext%7Bidentifier%5B=%5Dexpr%5B;%5D%7D%5C%5C%5Ctext%7BifStmt%7D&%5Cto%5Bsi%5D%5B%28%5D%5Ctext%7Bexpr%7D%5B%29%5D%5B%5Ctext%7B%5C%7B%7D%5D%5Ctext%7Bstatement%7D*%5B%5Ctext%7B%5C%7D%7D%5D%28%5Bsinon%5D%5B%5Ctext%7B%5C%7B%7D%5D%5Ctext%7Bstatement%7D*%5B%5Ctext%7B%5C%7D%7D%5D%29?%5C%5C%5Ctext%7Bexpr%7D&%5Cto%5Ctext%7Barithmetic%7D%5C%28%28%5Ctext%7B==%7D%7C%5Ctext%7B!=%7D%7C%3C%7C%5Cleq%7C%3E%7C%5Cgeq%29%5Ctext%7Barithmetic%7D%29*%5C%5C%5Ctext%7Barithmetic%7D&%5Cto%5Ctext%7Bterm%7D%5C%28%28%5B+%5D%7C%5B-%5D%29%5Ctext%7Bterm%7D%29*%5C%5C%5Ctext%7Bterm%7D&%5Cto%5Ctext%7Bfactor%7D%5C%28%28%5B*%5D%7C%5B/%5D%29%5Ctext%7Bfactor%7D%29*%5C%5C%5Ctext%7Bfactor%7D&%5Cto%5B%28%5D%5Ctext%7Bexpr%7D%5B%29%5D%5C;%7C%5C;%5Ctext%7Bprimary%7D%5C%5C%5Ctext%7Bprimary%7D&%5Cto%5Ctext%7Bnumber%7D%5C;%7C%5C;%5Ctext%7Bidentifier%7D%5C%5C%5Ctext%7Bidentifier%7D&%5Cto%5Ctext%7Bletter%7D%5C%28%28%5B%5Ctext%7Bletter%7D%5D%7C%5B%5Ctext%7Bdigit%7D%5D%29*%5C%5C%5Ctext%7Bnumber%7D&%5Cto%5Ctext%7Bdigit%7D%5C%5C%5Ctext%7Bletter%7D&%5Cto%5Ctext%7B%5Ba-zA-Z%5D%7D%5C%5C%5Ctext%7Bdigit%7D&%5Cto%5Ctext%7B%5B0-9%5D%7D%5Cend%7Balign*%7D$$)
